#pragma once

#include "Session.h"

#include <utility>

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
	void SetPlayer(PlayerPtr player) { m_Player = std::move(player); }
	PlayerPtr GetPlayer();

private:

	PlayerPtr m_Player;
};

