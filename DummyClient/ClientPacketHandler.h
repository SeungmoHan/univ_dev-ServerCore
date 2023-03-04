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
class ClientPacketHandler
{
public:

	static void HandlePacket(BYTE* buffer, const uint32 len);

	static void Handle_SC_TEST(BYTE* buffer, const uint32 len);
};

