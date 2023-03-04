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

void ClientPacketHandler::Handle_SC_TEST(BYTE* buffer, const uint32 len)
{
	BufferReader reader(buffer, len);
	PacketHeader header{};
	reader >> header;

	uint64 id;
	uint32 hp;
	uint16 attack;
	uint16 buffCount;
	reader >> id >> hp >> attack >> buffCount;

	vector<BuffData> buffs;
	buffs.resize(buffCount);

	for(uint32 i = 0; i< buffCount ; i++)
	{
		reader >> buffs[i].buffId >> buffs[i].remainTime;
	}
	

	cout << "ID : " << id << " HP : " << hp << " ATTACK : " << attack << endl;
	cout << "Buff count : " << buffCount << endl;
	for(uint32 i=0; i< buffCount; i++)
	{
		cout << "Buff ID : " << buffs[i].buffId << " BuffRemainTime : " << buffs[i].remainTime << endl;
	}
}
