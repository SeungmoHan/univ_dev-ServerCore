#include "pch.h"
#include "Room.h"

#include "GameSession.h"
#include "Player.h"
shared_ptr<Room> g_Room = MakeShared<Room>();

void Room::Enter(PlayerRef player)
{
	m_PlayerMap[player->m_PlayerId] = player;
}

void Room::Leave(PlayerRef player)
{
	m_PlayerMap.erase(player->m_PlayerId);
}

void Room::Broadcast(SendBufferRef sendBuffer)
{
	for(const auto& [playerId, player] : m_PlayerMap)
	{
		player->m_OwnerSession->Send(sendBuffer);
	}
}