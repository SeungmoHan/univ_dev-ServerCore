#include "pch.h"
#include "Player.h"
#include "Channel.h"
#include "ChannelManager.h"
#include "GameServer.h"
#include "GameSession.h"
#include "UpdateTickControl.h"

PlayerPtr Channel::GetPlayer(const uint64 playerId)
{
	auto itr = m_PlayerMap.find(playerId);
	if (itr == m_PlayerMap.end())
		return nullptr;
	if (itr->second->GetPlayerGuid() != playerId)
	{
		return nullptr;
	}
	return itr->second;
}



void Channel::Init(const ChannelOption& channelOption, const ptr<GameServer>& owner)
{
	m_OwnerServer = owner;
	m_ChannelOption = channelOption;
	m_ChannelStartFlag = true;
	m_UpdateControl = MakeShared<UpdateTickControl>(m_OwnerServer->GetServerOption().m_ServerFPS);
}

void Channel::Run()
{
	this_thread::sleep_for(5s);
	while (m_ChannelCloseFlag == false)
	{
		if (Update(m_UpdateControl->GetDeltaTick()) == false)
		{
			break;
		}
		m_UpdateControl->Update();
	}
}

void Channel::Clear()
{
	RemoveAllPlayer();
}

bool Channel::Update(uint64 deltaTick)
{
	for(auto [playerKey, player] : m_PlayerMap)
	{
		player->Update(deltaTick);
	}
	return true;
}

// MoveChannel Req
void Channel::MoveChannel(const uint32 toKey, PlayerPtr player)
{
	// 다음채널 가져옴...
	const auto nextChannel = ChannelManager::Instance().GetChannel(toKey);
	if (nextChannel == nullptr)
		return;
	// 다음채널로 갈 수 있다고 판단이 되어야 플레이어 지울거임...
	if(nextChannel->CanEnter())
	{
		// 지금 있는 채널에서 리무브
		RemovePlayer(player);
		// 3. 그 채널에 플레이어 add, 잡으로 넣어야 동기화 관련 문제가 안생김
		nextChannel->DoAsync(&Channel::AddPlayer, player);
	}
}

void Channel::MoveChannel(const uint32 toKey, const uint64 playerKey)
{
	const auto itr = m_PlayerMap.find(playerKey);
	if (itr == m_PlayerMap.end())
		return;
	const auto player = itr->second;
	return MoveChannel(toKey, player);
}

void Channel::Close()
{
	m_ChannelCloseFlag = true;
}

void Channel::RemoveAllPlayer()
{
	// 1 플레이어 정리
	for(auto [id, player] : m_PlayerMap)
	{
		// OnDisconnect가 올라왔을 때 player에 대한 뒷처리... 일단은 디스커넥트 처리만 하고나감
		player->GetOwnerSession()->Disconnect(L"Channel Shutdown");
	}
	// 2 맵에 남아있는 필드들 정리...
	// 3 그 외에 정리 할게 뭐가있을까? 일단은 없는 듯...
}

bool Channel::CanEnter() const
{
	// 일단 기본 조건은 플레이어 수가 꽉찼는지 확인...
	// 하지만 추후에 엔터가능한 조건이 추가될 예정임...
	return m_ChannelOption._maxPlayerCounts > m_ChannelOption._curPlayerCounts;
}



// 이게 불린거면 무조건 엔터가능한 상황임... 이전에 CanEnter로 체크해야함...
void Channel::AddPlayer(PlayerPtr player)
{
	auto playerKey = player->GetPlayerGuid();
	if (const auto itr = m_PlayerMap.find(playerKey); itr == m_PlayerMap.end())
		return;
	m_PlayerMap.emplace(playerKey, player);
	m_ChannelOption._curPlayerCounts++;
}


void Channel::RemovePlayer(const uint64 playerKey)
{
	const auto itr = m_PlayerMap.find(playerKey);
	if (itr == m_PlayerMap.end())
		return;
	m_PlayerMap.erase(playerKey);
	m_ChannelOption._curPlayerCounts--;
}

void Channel::RemovePlayer(PlayerPtr player)
{
	return RemovePlayer(player->GetPlayerGuid());
}
