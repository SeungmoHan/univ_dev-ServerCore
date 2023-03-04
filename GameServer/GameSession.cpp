#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"

void	GameSession::OnConnect() 
{
	GameSessionManager::Instance()->Add(static_pointer_cast<GameSession>(shared_from_this()));
};

int32	GameSession::OnRecv(BYTE* buffer, int32 len)
{
	//cout << "OnRecv Len =" << len << "  : " << (char*)buffer << endl;
	SendBufferRef sendBuffer = g_SendBufferManager->Open(4096);
	memcpy_s(sendBuffer->Buffer(), len, buffer, len);
	sendBuffer->Close(len);

	GameSessionManager::Instance()->Broadcast(sendBuffer);

	return len;
}

void	GameSession::OnSend(int32 len)
{
	//cout << "OnSend Len =" << len << endl;
};

void	GameSession::OnDisconnected() 
{
	GameSessionManager::Instance()->Remove(static_pointer_cast<GameSession>(shared_from_this()));
};