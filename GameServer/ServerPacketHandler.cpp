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

SendBufferRef ServerPacketHandler::Make_SC_TEST(const uint64 id, const uint32 hp, const uint16 attack, const vector<BuffData>& buffs, std::wstring name)
{
	SendBufferRef sendBuffer = g_SendBufferManager->Open(4096);

	BufferWriter writer(sendBuffer->Buffer(), 4096);

	auto* header = writer.Reserve<PacketHeader>();

	//id(uint64), 체력 uint32, 공격력 uint16
	writer << id << hp << attack;
#pragma pack(1)
	struct ListHeader
	{
		uint16 offSet;
		uint16 count;
	};
#pragma pack()

	const auto buffHeader = writer.Reserve<ListHeader>();
	buffHeader->count = static_cast<uint16>(buffs.size());
	buffHeader->offSet = static_cast<uint16>(writer.WriteSize());
	for(const auto [buffId, remainTime] : buffs)
		writer << buffId << remainTime;

	header->size = static_cast<uint16>(writer.WriteSize());
	header->id = SC_TEST;


	sendBuffer->Close(writer.WriteSize());
	return sendBuffer;
}
