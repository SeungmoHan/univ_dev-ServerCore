#include "pch.h"
#include "ClientPacketHandler.h"

#include "Channel.h"
#include "ChannelManager.h"
#include "GameRoomManager.h"
#include "GameServer.h"
#include "Player.h"
#include "Room.h"
#include "GameSession.h"

PacketHandlerFunc g_PacketHandler[UINT16_MAX];

// 직접 컨텐츠 작업자
bool Handle_INVALID(PacketSessionPtr& session, BYTE* buffer, const uint32 len)
{
	auto header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO Log...
	return false;
}

bool Handle_CS_LOGIN(PacketSessionPtr& session, Protocol::CS_LOGIN& pkt)
{
	const GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);

	// TODO validation

	Protocol::SC_LOGIN loginPacket;
	// 로그인 관련해서는 무조건 성공처리 한다...
	loginPacket.set_success(true);

	vector<uint32> channelIds;
	ChannelManager::Instance().GetChannelIDs(channelIds);
	for(const auto channelId : channelIds)
	{
		auto channel = ChannelManager::Instance().GetChannel(channelId);
		if (channel == nullptr)
		{
			//??
			continue;
		}

		const auto channelData = loginPacket.add_channels();
		auto& [channelKey, 
				channelName, 
				maxCounts, 
				curCounts] = channel->GetChannelOption();
		channelData->set_channelindex(channelKey);
		channelData->set_channelname(channelName.c_str(), channelName.size() * sizeof(wchar_t));
		channelData->set_usercounts(curCounts);
		channelData->set_maxchanneluser(maxCounts);
	}

	const auto sendBuffer = ClientPacketHandler::MakeSendBuffer(loginPacket);
	session->Send(sendBuffer);

	return false;
}

bool Handle_CS_ENTER_GAME(PacketSessionPtr& session, Protocol::CS_ENTER_GAME& pkt)
{
	const GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);

	const uint64 index = pkt.playerindex();
	//TODO validation
	gameSession->SetSelectedPlayer(index);
	const auto player = gameSession->GetSelectedPlayer();
	const auto room = player->SetCurrentRoom(GameRoomManager::Instance().GetDefaultEnterRoom());
	if (room == nullptr)
		return false;

	room->DoAsync(&Room::Enter, player);

	Protocol::SC_ENTER_GAME enterGamePacket;
	enterGamePacket.set_success(true);

	const auto sendBuffer = ClientPacketHandler::MakeSendBuffer(enterGamePacket);
	player->SendPacket(sendBuffer);

	return true;
}

bool Handle_CS_NORMAL_CHAT(PacketSessionPtr& session, Protocol::CS_NORMAL_CHAT& pkt)
{
	const GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	if (gameSession == nullptr)
		return false;
	const PlayerPtr player = gameSession->GetSelectedPlayer();
	if (player == nullptr)
		return false;

	Protocol::SC_NORMAL_CHAT chatPacket;
	chatPacket.set_playerid(player->GetPlayerGuid());
	chatPacket.set_playername(player->GetPlayerName());
	chatPacket.set_msg(pkt.msg());


	const auto sendBuffer = ClientPacketHandler::MakeSendBuffer(chatPacket);
	const auto room = player->GetCurrentRoom();
	if (room == nullptr)
		return false;
	room->DoAsync(&Room::Broadcast, sendBuffer);

	return true;
}


