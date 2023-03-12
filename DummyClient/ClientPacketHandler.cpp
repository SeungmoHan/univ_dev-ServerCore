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

	for(auto& buff : list)
	{
		cout << "BuffInfo : " << buff.buffId << " RemainTime : " << buff.remainTime << endl;

		PKT_SC_TEST::BuffVictimList victims = pkt->GetBuffVictimList(&buff);

		cout << "	Victim Count : " << victims.GetCount() << endl;
		for(const auto& victim : victims)
		{
			cout << "		Victime ID : " << victim << endl;
		}
	}
}
