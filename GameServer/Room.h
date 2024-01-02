#pragma once
#include "JobSerializer.h"

class Room : public JobSerializer
{
public:
	void Enter(PlayerPtr player);
	void Leave(PlayerPtr player);
	void Broadcast(SendBufferPtr sendBuffer);

private:
	USE_LOCK;
	map<uint64, PlayerPtr> m_PlayerMap;
	Atomic<bool> m_UseFlag = false;
};


extern shared_ptr<Room> g_Room;
