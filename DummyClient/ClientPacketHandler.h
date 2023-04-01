#pragma once

enum
{
	// Client To Server
	CS_TEST = 1,


	// Server To Client
	SC_TEST = 10001,
};


class ClientPacketHandler
{
public:

	static void HandlePacket(BYTE* buffer, const uint32 len);

	static void Handle_SC_TEST(const BYTE* buffer, const uint32 len);
};

