#pragma once
#include "Protocol.pb.h"

using PacketHandlerFunc = std::function<bool(PacketSessionPtr&, BYTE*, const uint32)>;
extern PacketHandlerFunc g_PacketHandler[UINT16_MAX];

enum : uint16
{
	CS_LOGIN_REQ = 1000,
	SC_LOGIN_RES = 1001,
	CS_CHANNEL_SELECT_REQ = 1002,
	SC_CHANNEL_SELECT_RES = 1003,
	CS_CHAR_LIST_REQ = 1004,
	SC_CHAR_LIST_RES = 1005,
	CS_CHAR_SELECT_REQ = 1006,
	SC_CHAR_SELECT_RES = 1007,
	CS_MOVE_REQ = 1008,
	SC_MOVE_RES = 1009,
	CS_MOVE_CHANNEL_REQ = 1010,
	SC_MOVE_CHANNEL_RES = 1011,
	CS_NORMAL_CHAT_REQ = 1012,
	SC_NORMAL_CHAT_RES = 1013,
	SC_CREATE_PLAYER_CMD = 1014,
	SC_DELETE_PLAYER_CMD = 1015,
	SC_POSITION_SYNC = 1016,
};

//Custom Handlers
bool Handle_INVALID(PacketSessionPtr& session, BYTE* buffer, const uint32 len);
bool Handle_CS_LOGIN_REQ(PacketSessionPtr& session, Protocol::CS_LOGIN_REQ& pkt);
bool Handle_CS_CHANNEL_SELECT_REQ(PacketSessionPtr& session, Protocol::CS_CHANNEL_SELECT_REQ& pkt);
bool Handle_CS_CHAR_LIST_REQ(PacketSessionPtr& session, Protocol::CS_CHAR_LIST_REQ& pkt);
bool Handle_CS_CHAR_SELECT_REQ(PacketSessionPtr& session, Protocol::CS_CHAR_SELECT_REQ& pkt);
bool Handle_CS_MOVE_REQ(PacketSessionPtr& session, Protocol::CS_MOVE_REQ& pkt);
bool Handle_CS_MOVE_CHANNEL_REQ(PacketSessionPtr& session, Protocol::CS_MOVE_CHANNEL_REQ& pkt);
bool Handle_CS_NORMAL_CHAT_REQ(PacketSessionPtr& session, Protocol::CS_NORMAL_CHAT_REQ& pkt);

class ClientPacketHandler
{
public:
	static void Init()
	{
		for (auto& handler : g_PacketHandler)
			handler = Handle_INVALID;
		g_PacketHandler[CS_LOGIN_REQ] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::CS_LOGIN_REQ>(Handle_CS_LOGIN_REQ, session, buffer, len); };
		g_PacketHandler[CS_CHANNEL_SELECT_REQ] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::CS_CHANNEL_SELECT_REQ>(Handle_CS_CHANNEL_SELECT_REQ, session, buffer, len); };
		g_PacketHandler[CS_CHAR_LIST_REQ] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::CS_CHAR_LIST_REQ>(Handle_CS_CHAR_LIST_REQ, session, buffer, len); };
		g_PacketHandler[CS_CHAR_SELECT_REQ] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::CS_CHAR_SELECT_REQ>(Handle_CS_CHAR_SELECT_REQ, session, buffer, len); };
		g_PacketHandler[CS_MOVE_REQ] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::CS_MOVE_REQ>(Handle_CS_MOVE_REQ, session, buffer, len); };
		g_PacketHandler[CS_MOVE_CHANNEL_REQ] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::CS_MOVE_CHANNEL_REQ>(Handle_CS_MOVE_CHANNEL_REQ, session, buffer, len); };
		g_PacketHandler[CS_NORMAL_CHAT_REQ] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::CS_NORMAL_CHAT_REQ>(Handle_CS_NORMAL_CHAT_REQ, session, buffer, len); };
	}

	static bool HandlePacket(PacketSessionPtr& session, BYTE* buffer, const uint32 len)
	{
		const auto header = reinterpret_cast<PacketHeader*>(buffer);
		return g_PacketHandler[header->id](session, buffer, len);
	}
	static SendBufferPtr MakeSendBuffer(const Protocol::SC_LOGIN_RES& pkt) { return MakeSendBuffer(pkt, SC_LOGIN_RES); }
	static SendBufferPtr MakeSendBuffer(const Protocol::SC_CHANNEL_SELECT_RES& pkt) { return MakeSendBuffer(pkt, SC_CHANNEL_SELECT_RES); }
	static SendBufferPtr MakeSendBuffer(const Protocol::SC_CHAR_LIST_RES& pkt) { return MakeSendBuffer(pkt, SC_CHAR_LIST_RES); }
	static SendBufferPtr MakeSendBuffer(const Protocol::SC_CHAR_SELECT_RES& pkt) { return MakeSendBuffer(pkt, SC_CHAR_SELECT_RES); }
	static SendBufferPtr MakeSendBuffer(const Protocol::SC_MOVE_RES& pkt) { return MakeSendBuffer(pkt, SC_MOVE_RES); }
	static SendBufferPtr MakeSendBuffer(const Protocol::SC_MOVE_CHANNEL_RES& pkt) { return MakeSendBuffer(pkt, SC_MOVE_CHANNEL_RES); }
	static SendBufferPtr MakeSendBuffer(const Protocol::SC_NORMAL_CHAT_RES& pkt) { return MakeSendBuffer(pkt, SC_NORMAL_CHAT_RES); }
	static SendBufferPtr MakeSendBuffer(const Protocol::SC_CREATE_PLAYER_CMD& pkt) { return MakeSendBuffer(pkt, SC_CREATE_PLAYER_CMD); }
	static SendBufferPtr MakeSendBuffer(const Protocol::SC_DELETE_PLAYER_CMD& pkt) { return MakeSendBuffer(pkt, SC_DELETE_PLAYER_CMD); }
	static SendBufferPtr MakeSendBuffer(const Protocol::SC_POSITION_SYNC& pkt) { return MakeSendBuffer(pkt, SC_POSITION_SYNC); }
private:

	template <typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, PacketSessionPtr& session, BYTE* buffer, const uint32 len)
	{
		PacketType pkt;
		if (false == pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)))
			return false;

		return func(session, pkt);
	}

	template <typename T>
	static SendBufferPtr MakeSendBuffer(const T& pkt, const uint16 pktId)
	{
		const auto dataSize = static_cast<uint16>(pkt.ByteSizeLong());
		const uint16 packetSize = dataSize + sizeof(PacketHeader);

		SendBufferPtr sendBuffer = g_SendBufferManager->Open(packetSize);
		const auto header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
		header->size = packetSize;
		header->id = pktId;
		ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
		sendBuffer->Close(packetSize);

		return sendBuffer;
	}
};

template <typename T>
SendBufferPtr _MakeSendBuffer(const T& pkt, const uint16 pktId)
{
	const auto dataSize = static_cast<uint16>(pkt.ByteSizeLong());
	const uint16 packetSize = dataSize + sizeof(PacketHeader);

	SendBufferPtr sendBuffer = g_SendBufferManager->Open(packetSize);
	const auto header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
	header->size = packetSize;
	header->id = pktId;
	ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
	sendBuffer->Close(packetSize);

	return sendBuffer;
}