#pragma once
#include "ClientPlayer.h"
class ClientPlayer;

class DummyStructManager
{
public:
	enum LockIndex
	{
		PlayerMapLock = 0,
		ReadyPlayerMapLock,
		LOCK_CNT_MAX,
	};
	static DummyStructManager& Instance()
	{
		static DummyStructManager instance;
		return instance;
	}
	void AddClientPlayer(const uint64 key, ptr<ClientPlayer> newPlayer);
	void RemoveClientPlayer(const uint64 key);
	ptr<ClientPlayer> GetClient(const uint64 key);

	void AddReadyPlayer(ptr<ClientPlayer> player);
	void RemoveReadyPlayer(uint64 key);

	void Update()
	{
		READ_LOCK_IDX(ReadyPlayerMapLock);
		for(const auto& [key,client] : m_ReadyPlayerMap)
		{
			if (client->_finished_to_set.load() == false)
				continue;
			client->Update();
		}
	}

private:
	DummyStructManager() = default;
	USE_LOCKS(LOCK_CNT_MAX);
	unordered_map<uint64, ptr<ClientPlayer>> m_PlayerMap;
	unordered_map<uint64, ptr<ClientPlayer>> m_ReadyPlayerMap;
};
