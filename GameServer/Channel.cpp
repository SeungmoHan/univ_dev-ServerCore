#include "pch.h"
#include "Player.h"
#include "Channel.h"
#include "ChannelManager.h"
#include "Field.h"
#include "GameServer.h"
#include "GameSession.h"
#include "Room.h"
#include "UpdateTickControl.h"

PlayerPtr Channel::GetPlayer(const uint64 playerId)
{
	auto itr = m_PlayerMap.find(playerId);
	if (itr == m_PlayerMap.end())
		return nullptr;
	if (itr->second->GetPlayerKey() != playerId)
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
	m_StartField = nullptr;
	m_UpdateControl = MakeShared<UpdateTickControl>(m_OwnerServer->GetServerOption().m_ServerFPS);

	if(m_ChannelOption._channelKey == ChannelManager::Instance().DefaultChannelID())
		m_ChannelOption._maxPlayerCounts = std::numeric_limits<uint32>::max();

	// 나중엔 여기서 스크립트에서 읽은 것들만 넣도록 해야함... FieldInfo.txt... 같은거
	FieldPtr startField = MakeShared<Field>();
	startField->Init();
	
	m_FieldMap.emplace(startField->GetFieldCode(), startField);
}

void Channel::Run()
{
	this_thread::sleep_for(5s);
	m_UpdateControl->Init();
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
	if (this->GetChannelOption()._channelKey == ChannelManager::Instance().DefaultChannelID())
		return true;

	// 채널에서는 플레이어들 업데이트,,,
	// 커뮤니티와 관련된 데이터 = 플레이어로 관리
	for(auto[playerKey, player] : m_PlayerMap)
	{
		if (player == nullptr)
			continue;
		player->Update(deltaTick);
	}
	// 필드들 업데이트
	// 필드 내에서 캐릭터 업데이트
	// 전투와 관련된 업데이트는 다 필드에서...
	for(auto [fieldKey, field] : m_FieldMap)
	{
		if(field != nullptr)
		{
			// field 안에서 Character들 업데이트 처리...
			field->Update(deltaTick);
		}
	}
	// 채널에 있는 룸(파티)들 업데이트
	for(auto [roomKey, room] : m_RoomMap)
	{
		if(room != nullptr)
		{
			room->Update(deltaTick);
		}
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
		RemovePlayer(player->GetPlayerKey());
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

void Channel::EnterField(const uint64 fieldCode, PlayerPtr player)
{
	auto itr = m_FieldMap.find(fieldCode);
	if (itr == m_FieldMap.end())
		return;
	const auto character = player->GetSelectedCharacter();
	const auto field = itr->second;
	field->DoAsync(&Field::AddPlayer, character);
}

uint64 Channel::GetStartFieldCode()
{
	if (m_StartField == nullptr)
		return numeric_limits<uint64>::max();
	return m_StartField->GetFieldCode();

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
	auto playerKey = player->GetPlayerKey();
	if (const auto itr = m_PlayerMap.find(playerKey); itr == m_PlayerMap.end())
		return;
	m_PlayerMap.emplace(playerKey, player);
	m_ChannelOption._curPlayerCounts++;
	player->DoAsync(&Player::OnEnterChannel, static_pointer_cast<Channel>(shared_from_this()));
}


void Channel::RemovePlayer(const uint64 playerKey)
{
	const auto itr = m_PlayerMap.find(playerKey);
	if (itr == m_PlayerMap.end())
		return;
	PlayerPtr player = itr->second;
	m_PlayerMap.erase(playerKey);
	m_ChannelOption._curPlayerCounts--;
	if (player == nullptr)
		return;

	const auto field = player->GetCurrentField();
	field->DoAsync(&Field::LeavePlayer, player->GetSelectedCharacter());
}
