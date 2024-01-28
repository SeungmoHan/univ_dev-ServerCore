#include "pch.h"
#include "DummyStructManager.h"

//PlayerMapLock,
//ReadyPlayerMapLock,
void DummyStructManager::AddClientPlayer(const uint64 key, ptr<ClientPlayer> newPlayer)
{
	WRITE_LOCK_IDX(PlayerMapLock);
	m_PlayerMap.emplace(key, newPlayer);
}

void DummyStructManager::RemoveClientPlayer(const uint64 key)
{
	WRITE_LOCK_IDX(PlayerMapLock);
	if (const auto itr = m_PlayerMap.find(key); itr == m_PlayerMap.end())
		return;
	m_PlayerMap.erase(key);
}

ptr<ClientPlayer> DummyStructManager::GetClient(const uint64 key)
{
	READ_LOCK_IDX(PlayerMapLock);
	if(m_PlayerMap.find(key) == m_PlayerMap.end())
		return nullptr;
	return m_PlayerMap[key];
}

void DummyStructManager::AddReadyPlayer(ptr<ClientPlayer> player)
{
	if (player->_finished_to_set.exchange(true) == true)
		return;
	{
		WRITE_LOCK_IDX(ReadyPlayerMapLock);
		m_ReadyPlayerMap.emplace(player->_key, player);
	}

}

void DummyStructManager::RemoveReadyPlayer(uint64 key)
{
	WRITE_LOCK_IDX(ReadyPlayerMapLock);
	const auto itr = m_ReadyPlayerMap.find(key);
	if (itr == m_ReadyPlayerMap.end())
		return;
	const auto player = itr->second;
	m_ReadyPlayerMap.erase(key);
	player->_finished_to_set.exchange(false);
}
