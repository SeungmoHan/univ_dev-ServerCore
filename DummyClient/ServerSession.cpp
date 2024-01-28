#include "pch.h"
#include "ServerSession.h"

#include "Protocol.pb.h"
#include "ServerPacketHandler.h"

void ServerSession::OnConnect()
{
	static Atomic<uint64> dummyKey = 0;
	const Protocol::CS_LOGIN_REQ loginPacket;
	const auto buffer = ServerPacketHandler::MakeSendBuffer(loginPacket);
	Send(buffer);

	ClientPlayerPtr newClient = MakeShared<ClientPlayer>();
	newClient->_ownerSession = static_pointer_cast<ServerSession>(shared_from_this());
	id = dummyKey.fetch_add(1);
	newClient->_key = id;
	DummyStructManager::Instance().AddClientPlayer(id, newClient);
}


void	ServerSession::OnRecvPacket(BYTE* buffer, const int32 len)
{
	auto session = GetPacketSessionPtr();
	auto header = reinterpret_cast<PacketHeader*>(buffer);

	ServerPacketHandler::HandlePacket(session, buffer, len);
}

void ServerSession::OnDisconnected()
{
	DummyStructManager::Instance().RemoveClientPlayer(id);
}
