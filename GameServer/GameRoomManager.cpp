#include "pch.h"
#include "GameRoomManager.h"

#include "Player.h"
#include "Room.h"

void GameRoomManager::Update(const uint64 deltaTick)
{
	for(auto [roomKey, room] : m_RoomMap)
	{
		room->Update(deltaTick);
	}
}

void GameRoomManager::CreateRoom()
{
	uint64 roomKey = m_RoomKeyGenerator.fetch_add(1);
	auto newRoom = MakeShared<Room>();
	newRoom->Init(roomKey);
	m_RoomMap.emplace(roomKey, newRoom);
}

void GameRoomManager::EnterRoom(const uint64 roomKey, const PlayerPtr& player)
{
	const auto itr = m_RoomMap.find(roomKey);
	if (itr == m_RoomMap.end())
		return;
	const ptr<Room> room = itr->second;
	room->DoAsync(&Room::Enter, player);
}

void GameRoomManager::LeaveRoom(const uint64 roomKey, const PlayerPtr& player)
{
	const auto itr = m_RoomMap.find(roomKey);
	if (itr == m_RoomMap.end())
		return;
	const ptr<Room> gameRoom = itr->second;

	gameRoom->DoAsync<Room, void>(&Room::Leave, player->GetPlayerGuid());
}

void GameRoomManager::EraseRoom(const uint64 roomKey)
{
	m_RoomMap.erase(roomKey);
}

GameRoomManager::GameRoomManager()
{
	CreateRoom();
}
