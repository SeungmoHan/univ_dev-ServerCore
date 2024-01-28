#include "pch.h"
#include "GameSession.h"

#include "Channel.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"
#include "Room.h"
#include "Player.h"

void	GameSession::OnConnect()
{
	GameSessionManager::Instance()->Add(static_pointer_cast<GameSession>(shared_from_this()));
};

void	GameSession::OnRecvPacket(BYTE* buffer, const int32 len)
{
	auto session = GetPacketSessionPtr();
	auto header = reinterpret_cast<PacketHeader*>(buffer);

	//TODO PacketID 대역 체크
	ClientPacketHandler::HandlePacket(session, buffer, len);
}

void	GameSession::OnSend(int32 len)
{

};

void	GameSession::OnDisconnected() 
{
	m_Player->OnDisconnected();
	GameSessionManager::Instance()->Remove(static_pointer_cast<GameSession>(shared_from_this()));
	m_Player = nullptr;
}



PlayerPtr GameSession::GetPlayer()
{
	return m_Player;
}
