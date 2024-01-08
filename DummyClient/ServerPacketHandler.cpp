#include "pch.h"
#include "ServerPacketHandler.h"
#include "ClientPlayer.h"
#include "ServerSession.h"

PacketHandlerFunc g_PacketHandler[UINT16_MAX];

// 직접 컨텐츠 작업자
bool Handle_INVALID(PacketSessionPtr& session, BYTE* buffer, const uint32 len)
{
	auto header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO Log...
	return false;
}

bool Handle_SC_LOGIN(PacketSessionPtr& session, Protocol::SC_LOGIN& pkt)
{
	if(pkt.success() == false)
	{
		// 로비로 튕겨내거나 한다
		return true;
	}
	
	Protocol::CS_ENTER_GAME enterGamePacket;
	enterGamePacket.set_playerindex(0);


	const auto sendBuffer = ServerPacketHandler::MakeSendBuffer(enterGamePacket);
	session->Send(sendBuffer);

	return true;
}

bool Handle_SC_CHAR_LIST(PacketSessionPtr& session, Protocol::SC_CHAR_LIST& pkt)
{
	return true;
}

bool Handle_SC_ENTER_GAME(PacketSessionPtr& session, Protocol::SC_ENTER_GAME& pkt)
{
	Protocol::CS_NORMAL_CHAT chatPkt;
	chatPkt.set_msg(u8"Begin Hello World!");
	const auto sendBuffer = ServerPacketHandler::MakeSendBuffer(chatPkt);
	session->Send(sendBuffer);

	return true;
}

bool Handle_SC_NORMAL_CHAT(PacketSessionPtr& session, Protocol::SC_NORMAL_CHAT& pkt)
{
	static Atomic<unsigned long long> atm = 0;
	ServerSessionPtr serverSession = reinterpret_pointer_cast<ServerSession>(session);

	ClientPlayerPtr clientPlayer = serverSession->m_SelectedPlayer;
	if(clientPlayer == nullptr)
		return false;
	if(pkt.playerid() != clientPlayer->m_PlayerID)
	{
		cout <<"MyID:" << clientPlayer->m_PlayerID << " | " << pkt.playerid() << "(" << pkt.playername() << ") : " << pkt.msg() << endl;
	}
	this_thread::sleep_for(100ms);

	string nextMsg = to_string(++atm) + " : Hello World!";
	Protocol::CS_NORMAL_CHAT chatPkt;
	chatPkt.set_msg(nextMsg);

	const auto sendBuffer = ServerPacketHandler::MakeSendBuffer(chatPkt);
	session->Send(sendBuffer);
	//cout << "Send" << endl;

	return true;
}

