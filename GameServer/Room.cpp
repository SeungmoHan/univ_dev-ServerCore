#include "pch.h"
#include "Room.h"

#include "GameSession.h"
#include "Player.h"
Room g_Room;

void Room::Enter(const PlayerRef& player)
{
	WRITE_LOCK;

	m_PlayerMap[player->m_PlayerId] = player;
}

void Room::Leave(const PlayerRef& player)
{
	WRITE_LOCK;

	m_PlayerMap.erase(player->m_PlayerId);
}

void Room::Broadcast(const SendBufferRef& sendBuffer)
{
	WRITE_LOCK;

	for(const auto& [playerId, player] : m_PlayerMap)
	{
		player->m_OwnerSession->Send(sendBuffer);
	}
}


