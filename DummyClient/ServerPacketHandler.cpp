#include "pch.h"
#include "ServerPacketHandler.h"

PacketHandlerFunc g_PacketHandler[UINT16_MAX];

// ���� ������ �۾���
bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, const uint32 len)
{
	auto header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO Log...
	return false;
}

bool Handle_SC_LOGIN(PacketSessionRef& session, Protocol::SC_LOGIN& pkt)
{
	if(pkt.success() == false)
	{
		// �κ�� ƨ�ܳ��ų� �Ѵ�
		return true;
	}

	if(pkt.players().empty())
	{
		// ĳ���� ����â
	}

	// ���� UI������ ����
	Protocol::CS_ENTER_GAME enterGamePacket;
	enterGamePacket.set_playerindex(1);

	const auto sendBuffer = ServerPacketHandler::MakeSendBuffer(enterGamePacket);
	session->Send(sendBuffer);

	return true;
}

bool Handle_SC_ENTER_GAME(PacketSessionRef& session, Protocol::SC_ENTER_GAME& pkt)
{



	return true;
}

bool Handle_SC_NORMAL_CHAT(PacketSessionRef& session, Protocol::SC_NORMAL_CHAT& pkt)
{

	std::cout << pkt.msg() << std::endl;

	return true;
}

