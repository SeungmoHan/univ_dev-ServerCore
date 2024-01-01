#pragma once

#include "Session.h"

class GameSession : public PacketSession
{
	DECLARE_TL(SessionTL);
public:
	virtual ~GameSession()
	{
		cout << "~GameSession" << endl;
	}
	virtual void	OnConnect() override;
	//virtual int32	OnRecv(BYTE* buffer, int32 len) override;
	virtual void	OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void	OnSend(int32 len) override;
	virtual void	OnDisconnected() override;

public:
	PlayerPtr GetSeleectedPlayer() const { return m_CurrentPlayer; }

public:
	Vector<PlayerPtr> m_Players;

	PlayerPtr m_CurrentPlayer;
	weak_ptr<class Room> m_Room;
};

