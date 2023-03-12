#include "pch.h"
#include "ClientPacketHandler.h"

#include "BufferReader.h"


void ClientPacketHandler::HandlePacket(BYTE* buffer, const uint32 len)
{
	BufferReader reader(buffer, len);

	PacketHeader header{};
	reader.Peek(&header);

	switch(header.id)
	{
	case SC_TEST:
		Handle_SC_TEST(buffer, len);
		break;
	default: break;
	}
}


//
//SC_TEST temp
// unsigned 64byte : id
// unsigned 32byte : hp
// unsigned 16byte : attack
// vector<...>...;
#pragma pack(1)
struct PKT_SC_TEST
{
	struct BuffListItem
	{
		uint64 buffId;
		float remainTime;
	};

	uint16 packetSize;
	uint16 packetId;

	uint64 id;
	uint32 hp;
	uint16 attack;

	uint16 buffOffset;
	uint16 buffCount;

	bool Validate() const
	{
		uint32 size = 0;

		size += sizeof(PKT_SC_TEST);

		if (packetSize < size)
			return false;

		size += buffCount * sizeof(BuffListItem);
		if (size != packetSize)
			return false;

		if (buffOffset + buffCount * sizeof(BuffListItem) > packetSize)
			return false;
		return true;
	}
	using BuffList = PacketList<BuffListItem>;

	BuffList GetBuffList()
	{
		auto data = reinterpret_cast<BYTE*>(this);
		data += buffOffset;
		return BuffList{ reinterpret_cast<BuffListItem*>(data), buffCount };
	}

};
#pragma pack()

void ClientPacketHandler::Handle_SC_TEST(BYTE* buffer, const uint32 len)
{
	BufferReader reader(buffer, len);

	if (len < sizeof(PKT_SC_TEST))
		return;

	const auto pkt = reinterpret_cast<PKT_SC_TEST*>(buffer);


	if (pkt->Validate() == false)
		return;

	auto list = pkt->GetBuffList();
	
	const uint32 listCount = list.GetCount();
	cout << "ID : " << pkt->id << " HP : " << pkt->hp << " ATTACK : " << pkt->attack << endl;
	cout << "Buff count : " << listCount << endl;

	for (const auto [buffId, remainTime] : list)
	{
		cout << "Buff ID : " << buffId << " BuffRemainTime : " << remainTime << endl;
	} 
}
