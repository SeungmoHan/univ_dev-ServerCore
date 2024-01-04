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

// true -> 룸 살려둬야함, false -> room destroy
bool Room::Leave(const PlayerPtr player)
{
	if(m_RoomLeader == player)
		m_RoomLeader = nullptr;

	m_PlayerMap.erase(player->GetPlayerGuid());

	if(m_PlayerMap.empty() && m_RoomKey != 1)
	{
		GameRoomManager::Instance().EraseRoom(m_RoomKey);
	}

	if (m_RoomLeader == nullptr)
		m_RoomLeader = m_PlayerMap.begin()->second;
	return true;
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
	for(const auto& [playerId, player] : m_PlayerMap)
	{
		GameSessionPtr ownerSession = player->GetOwnerSession();
		if (ownerSession == nullptr || ownerSession->IsConnected() == false)
			continue;

		//TODO Player Update 구현해두기
		player->Update();
	}
}

void Room::Init(uint64 roomKey)
{
	m_RoomKey = roomKey;
}




