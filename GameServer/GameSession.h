#pragma once

#include "Session.h"

class GameSession : public Session
{
	virtual void	OnConnect() override;
	virtual int32	OnRecv(BYTE* buffer, int32 len) override;
	virtual void	OnSend(int32 len) override;
	virtual void	OnDisconnected() override;
};

