#include "pch.h"
#include "ServerSession.h"

#include "Protocol.pb.h"
#include "ServerPacketHandler.h"


void ServerSession::OnConnect()
{
	Protocol::CS_LOGIN loginPacket;
	const auto buffer = ServerPacketHandler::MakeSendBuffer(loginPacket);
	Send(buffer);
}


void	ServerSession::OnRecvPacket(BYTE* buffer, const int32 len)
{
	auto session = GetPacketSessionPtr();
	auto header = reinterpret_cast<PacketHeader*>(buffer);

	ServerPacketHandler::HandlePacket(session, buffer, len);
}