#include "pch.h"
#include "ServerPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"


void ServerPacketHandler::HandlePacket(BYTE* buffer, const uint32 len)
{
	BufferReader reader(buffer, len);
	PacketHeader header{};
	reader.Peek(&header);

	switch (header.id)
	{
	case CS_TEST:
		Handle_CS_TEST(buffer, len); break;
	default: 
		break;
	}
}

void ServerPacketHandler::Handle_CS_TEST(BYTE* buffer, const uint32 len)
{
	BufferReader reader(buffer, len);
	PacketHeader header{};
	reader.Peek(&header);

	
}

SendBufferRef ServerPacketHandler::Make_SC_TEST(const uint64 id, const uint32 hp, const uint16 attack, const vector<BuffData>& datas)
{
	SendBufferRef sendBuffer = g_SendBufferManager->Open(4096);

	BufferWriter writer(sendBuffer->Buffer(), 4096);

	auto* header = writer.Reserve<PacketHeader>();

	//id(uint64), 체력 uint32, 공격력 uint16
	writer << id << hp << attack;


	// variable length data...
	writer << static_cast<uint16>(datas.size());
	for(const auto [buffId, remainTime] : datas)
	{
		writer << buffId << remainTime;
	}

	header->size = static_cast<uint16>(writer.WriteSize());
	header->id = SC_TEST;


	sendBuffer->Close(writer.WriteSize());
	return sendBuffer;
}
