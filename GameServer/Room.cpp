#include "pch.h"
#include "Room.h"

#include "GameRoomManager.h"
#include "GameSession.h"
#include "Player.h"

void Room::Enter(PlayerPtr player)
{
	if(m_PlayerMap.empty())
		m_RoomLeader = player;
	m_PlayerMap[player->GetPlayerGuid()] = player;
}

void Room::Leave(const PlayerPtr player)
{
	if(m_RoomLeader == player)
		m_RoomLeader = nullptr;

	m_PlayerMap.erase(player->GetPlayerGuid());

	if(m_PlayerMap.empty() && m_RoomKey != 1)
	{
		GameRoomManager::Instance().EraseRoom(m_RoomKey);
		return;
	}

	if (m_RoomLeader == nullptr)
		m_RoomLeader = m_PlayerMap.begin()->second;
}

void Room::Leave(uint64 playerGuid)
{
	const auto itr = m_PlayerMap.find(playerGuid);
	if (itr == m_PlayerMap.end())
		return;
	const auto player = itr->second;
	Leave(player);
}

void Room::Broadcast(SendBufferPtr sendBuffer)
{
	for(const auto& [playerId, player] : m_PlayerMap)
	{
		GameSessionPtr ownerSession = player->GetOwnerSession();
		if (ownerSession == nullptr || ownerSession->IsConnected() == false)
			continue;
		player->GetOwnerSession()->Send(sendBuffer);
	}
}

void Room::Update(uint64 deltaTick)
{
	// Room은 방과 관련된 업데이트만 치도록하자...
	// 업데이트 == 방에서 나가야할 사람들 정하기... 등등
	for(auto [playerid, player] : m_PlayerMap)
	{
		if(player->GetOwnerSession()->IsConnected() == false)
		{
			
		}
	}
}

void Room::Init(const uint64 roomKey)
{
	m_RoomKey = roomKey;
}




