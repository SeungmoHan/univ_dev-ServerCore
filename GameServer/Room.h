#pragma once
#include "JobSerializer.h"

class Room : public JobSerializer
{
public:
	virtual void Enter(PlayerPtr player);
	virtual void Leave(uint64 playerGuid);
	virtual void Broadcast(SendBufferPtr sendBuffer);
	virtual void Update(uint64 deltaTick);

	explicit Room() = default;
	~Room() override = default;
	void Init(uint64 roomKey);
private:
	virtual void Leave(PlayerPtr player);

	USE_LOCK;
	uint64 m_RoomKey = 0;
	PlayerPtr m_RoomLeader;
	map<uint64, PlayerPtr> m_PlayerMap;
	Atomic<bool> m_UseFlag = false;
};
