#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"

void	GameSession::OnConnect() 
{
	GameSessionManager::Instance()->Add(static_pointer_cast<GameSession>(shared_from_this()));
};

int32	GameSession::OnRecvPacket(BYTE* buffer, const int32 len)
{
	const auto [size, id] = *reinterpret_cast<PacketHeader*>(buffer);

	cout << "Packet ID : " << id << " Size : " << size << endl;
	//cout << "OnRecv Len =" << len << "  : " << (char*)buffer << endl;


	//GameSessionManager::Instance()->Broadcast(buffer);

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