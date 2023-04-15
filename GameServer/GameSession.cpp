#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"

void	GameSession::OnConnect() 
{
	GameSessionManager::Instance()->Add(static_pointer_cast<GameSession>(shared_from_this()));
};

void	GameSession::OnRecvPacket(BYTE* buffer, const int32 len)
{
	auto session = GetPacketSessionRef();
	auto header = reinterpret_cast<PacketHeader*>(buffer);

	//TODO PacketID 대역 체크
	ClientPacketHandler::HandlePacket(session, buffer, len);
}

void	GameSession::OnSend(int32 len)
{
	//cout << "OnSend Len =" << len << endl;
};

void	GameSession::OnDisconnected() 
{
	GameSessionManager::Instance()->Remove(static_pointer_cast<GameSession>(shared_from_this()));
};