#pragma once

#include "Session.h"

class GameSession : public PacketSession
{
	virtual void	OnConnect() override;
	//virtual int32	OnRecv(BYTE* buffer, int32 len) override;
	virtual int32	OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void	OnSend(int32 len) override;
	virtual void	OnDisconnected() override;
};

