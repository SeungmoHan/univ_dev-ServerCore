#pragma once

enum
{
	// Client To Server
	CS_TEST = 1,


	// Server To Client
	SC_TEST = 10001,
};


struct BuffData
{
	uint64 buffId;
	float remainTime;
};
class ServerPacketHandler
{
public:
	static void HandlePacket(BYTE* buffer, const uint32 len);

	static void Handle_CS_TEST(BYTE* buffer, const uint32 len);



	static SendBufferRef Make_SC_TEST(const uint64 id, const uint32 hp, const uint16 attack, const vector<BuffData>& buffs, std::wstring name);
};
