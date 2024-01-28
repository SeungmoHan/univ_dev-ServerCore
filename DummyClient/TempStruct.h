#pragma once
#include "Enum.pb.h"


struct ClientChannelData
{
	uint32 channelID = 0;
	wstring channelName;
	uint32 maxChannelUser = 0;
	uint32 curChannelUserCounts = 0;
};

struct ClientCharacterData
{
	uint64 id = 0;
	wstring name;
	Protocol::PlayerType type = Protocol::PLAYER_TYPE_NONE;

};