#pragma once
#include "JobSerializer.h"

class Room : public JobSerializer
{
public:
	void Enter(PlayerRef player);
	void Leave(PlayerRef player);
	void Broadcast(SendBufferRef sendBuffer);

	// multi thread 환경에서의 작업
public:
	virtual void FlushJob() override;


private:
	USE_LOCK;
	map<uint64, PlayerRef> m_PlayerMap;
	Atomic<bool> m_UseFlag = false;
};


extern shared_ptr<Room> g_Room;
