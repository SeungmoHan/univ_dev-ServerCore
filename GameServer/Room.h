#pragma once


class Room
{
public:
	void Enter(const PlayerRef& player);
	void Leave(const PlayerRef& player);

	void Broadcast(const SendBufferRef& sendBuffer);



private:
	USE_LOCK;
	map<uint64, PlayerRef> m_PlayerMap;
};

extern Room g_Room;