#pragma once

#include "Session.h"

class GameSession : public PacketSession
{
public:
	~GameSession()
	{
		cout << "~GameSession" << endl;
	}
	virtual void	OnConnect() override;
	//virtual int32	OnRecv(BYTE* buffer, int32 len) override;
	virtual void	OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void	OnSend(int32 len) override;
	virtual void	OnDisconnected() override;

public:
	Vector<PlayerRef> m_Players;

	PlayerRef m_CurrentPlayer;
	weak_ptr<class Room> m_Room;
};

