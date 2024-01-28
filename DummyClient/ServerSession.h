#pragma once
#include "Session.h"

class ServerSession : public PacketSession
{
	DECLARE_TL(SessionTL);
public:
	ServerSession()
	{
		INIT_TL(ServerSession);
	}

	virtual void	OnConnect() override;

	virtual void	OnRecvPacket(BYTE* buffer, const int32 len) override;

	virtual void	OnSend(int32 len) override
	{
	};
	virtual void	OnDisconnected() override;;

	uint64 id;
};
