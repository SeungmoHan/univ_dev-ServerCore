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
bool Handle_SC_LOGIN_RES(PacketSessionPtr& session, Protocol::SC_LOGIN_RES& pkt);
bool Handle_SC_CHANNEL_SELECT_RES(PacketSessionPtr& session, Protocol::SC_CHANNEL_SELECT_RES& pkt);
bool Handle_SC_CHAR_LIST_RES(PacketSessionPtr& session, Protocol::SC_CHAR_LIST_RES& pkt);
bool Handle_SC_CHAR_SELECT_RES(PacketSessionPtr& session, Protocol::SC_CHAR_SELECT_RES& pkt);
bool Handle_SC_MOVE_RES(PacketSessionPtr& session, Protocol::SC_MOVE_RES& pkt);
bool Handle_SC_MOVE_CHANNEL_RES(PacketSessionPtr& session, Protocol::SC_MOVE_CHANNEL_RES& pkt);
bool Handle_SC_NORMAL_CHAT_RES(PacketSessionPtr& session, Protocol::SC_NORMAL_CHAT_RES& pkt);
bool Handle_SC_CREATE_PLAYER_CMD(PacketSessionPtr& session, Protocol::SC_CREATE_PLAYER_CMD& pkt);
bool Handle_SC_DELETE_PLAYER_CMD(PacketSessionPtr& session, Protocol::SC_DELETE_PLAYER_CMD& pkt);
bool Handle_SC_POSITION_SYNC(PacketSessionPtr& session, Protocol::SC_POSITION_SYNC& pkt);

class ServerPacketHandler
{
public:
	static void Init()
	{
		for (auto& handler : g_PacketHandler)
			handler = Handle_INVALID;
		g_PacketHandler[SC_LOGIN_RES] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::SC_LOGIN_RES>(Handle_SC_LOGIN_RES, session, buffer, len); };
		g_PacketHandler[SC_CHANNEL_SELECT_RES] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::SC_CHANNEL_SELECT_RES>(Handle_SC_CHANNEL_SELECT_RES, session, buffer, len); };
		g_PacketHandler[SC_CHAR_LIST_RES] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::SC_CHAR_LIST_RES>(Handle_SC_CHAR_LIST_RES, session, buffer, len); };
		g_PacketHandler[SC_CHAR_SELECT_RES] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::SC_CHAR_SELECT_RES>(Handle_SC_CHAR_SELECT_RES, session, buffer, len); };
		g_PacketHandler[SC_MOVE_RES] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::SC_MOVE_RES>(Handle_SC_MOVE_RES, session, buffer, len); };
		g_PacketHandler[SC_MOVE_CHANNEL_RES] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::SC_MOVE_CHANNEL_RES>(Handle_SC_MOVE_CHANNEL_RES, session, buffer, len); };
		g_PacketHandler[SC_NORMAL_CHAT_RES] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::SC_NORMAL_CHAT_RES>(Handle_SC_NORMAL_CHAT_RES, session, buffer, len); };
		g_PacketHandler[SC_CREATE_PLAYER_CMD] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::SC_CREATE_PLAYER_CMD>(Handle_SC_CREATE_PLAYER_CMD, session, buffer, len); };
		g_PacketHandler[SC_DELETE_PLAYER_CMD] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::SC_DELETE_PLAYER_CMD>(Handle_SC_DELETE_PLAYER_CMD, session, buffer, len); };
		g_PacketHandler[SC_POSITION_SYNC] = [](PacketSessionPtr& session, BYTE* buffer, const uint32 len) {return HandlePacket<Protocol::SC_POSITION_SYNC>(Handle_SC_POSITION_SYNC, session, buffer, len); };
	}

	static bool HandlePacket(PacketSessionPtr& session, BYTE* buffer, const uint32 len)
	{
		const auto header = reinterpret_cast<PacketHeader*>(buffer);
		return g_PacketHandler[header->id](session, buffer, len);
	}
	static SendBufferPtr MakeSendBuffer(const Protocol::CS_LOGIN_REQ& pkt) { return MakeSendBuffer(pkt, CS_LOGIN_REQ); }
	static SendBufferPtr MakeSendBuffer(const Protocol::CS_CHANNEL_SELECT_REQ& pkt) { return MakeSendBuffer(pkt, CS_CHANNEL_SELECT_REQ); }
	static SendBufferPtr MakeSendBuffer(const Protocol::CS_CHAR_LIST_REQ& pkt) { return MakeSendBuffer(pkt, CS_CHAR_LIST_REQ); }
	static SendBufferPtr MakeSendBuffer(const Protocol::CS_CHAR_SELECT_REQ& pkt) { return MakeSendBuffer(pkt, CS_CHAR_SELECT_REQ); }
	static SendBufferPtr MakeSendBuffer(const Protocol::CS_MOVE_REQ& pkt) { return MakeSendBuffer(pkt, CS_MOVE_REQ); }
	static SendBufferPtr MakeSendBuffer(const Protocol::CS_MOVE_CHANNEL_REQ& pkt) { return MakeSendBuffer(pkt, CS_MOVE_CHANNEL_REQ); }
	static SendBufferPtr MakeSendBuffer(const Protocol::CS_NORMAL_CHAT_REQ& pkt) { return MakeSendBuffer(pkt, CS_NORMAL_CHAT_REQ); }
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