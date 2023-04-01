#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "Protocol.pb.h"


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


void ClientPacketHandler::Handle_SC_TEST(const BYTE* buffer, const uint32 len)
{
	Protocol::SC_TEST pkt;
	
	ASSERT_CRASH(pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)));

	cout << "pktId : " << pkt.id() << " pktHP : " << pkt.hp() << " pktAttack : " << pkt.attack() << endl;
	cout << "buffSize : " << pkt.buff_size() << endl;

	for(auto& buff : pkt.buff())
	{
		cout << "buffId : " << buff.buffid() << " remianTime : " << buff.remaintime() << endl;
		cout << "victimsSize : " << buff.victims_size() << endl;
		for(auto& victim : buff.victims())
		{
			cout << "victim : " << victim << endl;
		}
	}

}
