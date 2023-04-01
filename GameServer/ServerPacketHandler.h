#pragma once
#include "BufferReader.h"
#include "BufferWriter.h"
#include "Protocol.pb.h"
enum
{
	// Client To Server
	CS_TEST = 1,


	// Server To Client
	SC_TEST = 10001,
};

class ServerPacketHandler
{
public:
	static void HandlePacket(BYTE* buffer, const uint32 len);

	static void Handle_CS_TEST(BYTE* buffer, const uint32 len);

	static SendBufferRef MakeSendBuffer(const Protocol::SC_TEST& pkt);
	//static SendBufferRef Make_SC_TEST(const uint64 id, const uint32 hp, const uint16 attack, const vector<BuffData>& buffs, std::wstring name);
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
