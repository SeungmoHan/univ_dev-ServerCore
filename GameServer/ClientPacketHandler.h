#pragma once
#include "Protocol.pb.h"

using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, const uint32)>;
extern PacketHandlerFunc g_PacketHandler[UINT16_MAX];

enum : uint16
{
	CS_LOGIN = 1000,
	SC_LOGIN = 1001,
	CS_ENTER_GAME = 1002,
	SC_ENTER_GAME = 1003,
	CS_NORMAL_CHAT = 1004,
	SC_NORMAL_CHAT = 1005,
};

//Custom Handlers
bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, const uint32 len);
bool Handle_CS_LOGIN(PacketSessionRef& session, Protocol::CS_LOGIN& pkt);
bool Handle_CS_ENTER_GAME(PacketSessionRef& session, Protocol::CS_ENTER_GAME& pkt);
bool Handle_CS_NORMAL_CHAT(PacketSessionRef& session, Protocol::CS_NORMAL_CHAT& pkt);

class ClientPacketHandler
{
public:
	static void Init()
	{
		for (auto& handler : g_PacketHandler)
			handler = Handle_INVALID;
		g_PacketHandler[CS_LOGIN] = [](PacketSessionRef& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::CS_LOGIN>(Handle_CS_LOGIN, session, buffer, len); };
		g_PacketHandler[CS_ENTER_GAME] = [](PacketSessionRef& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::CS_ENTER_GAME>(Handle_CS_ENTER_GAME, session, buffer, len); };
		g_PacketHandler[CS_NORMAL_CHAT] = [](PacketSessionRef& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::CS_NORMAL_CHAT>(Handle_CS_NORMAL_CHAT, session, buffer, len); };
	}

	static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, const uint32 len)
	{
		const auto header = reinterpret_cast<PacketHeader*>(buffer);
		return g_PacketHandler[header->id](session, buffer, len);
	}
	static SendBufferRef MakeSendBuffer(const Protocol::SC_LOGIN& pkt) { return MakeSendBuffer(pkt, SC_LOGIN); }
	static SendBufferRef MakeSendBuffer(const Protocol::SC_ENTER_GAME& pkt) { return MakeSendBuffer(pkt, SC_ENTER_GAME); }
	static SendBufferRef MakeSendBuffer(const Protocol::SC_NORMAL_CHAT& pkt) { return MakeSendBuffer(pkt, SC_NORMAL_CHAT); }
private:

	template <typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, PacketSessionRef& session, BYTE* buffer, const uint32 len)
	{
		PacketType pkt;
		if (false == pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)))
			return false;

		return func(session, pkt);
	}

	template <typename T>
	static SendBufferRef MakeSendBuffer(const T& pkt, const uint16 pktId)
	{
		const auto dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferRef sendBuffer = g_SendBufferManager->Open(packetSize);
		const auto header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;
		ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}
};

template <typename T>
SendBufferRef _MakeSendBuffer(const T& pkt, const uint16 pktId)
{
	const auto dataSize = static_cast<uint16>(pkt.ByteSizeLong());
	const uint16 packetSize = dataSize + sizeof(PacketHeader);

	SendBufferRef sendBuffer = g_SendBufferManager->Open(packetSize);
	const auto header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
	header->size = packetSize;
	header->id = pktId;
	ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
	sendBuffer->Close(packetSize);

	return sendBuffer;
}