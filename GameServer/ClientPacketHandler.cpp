#include "pch.h"
#include "ClientPacketHandler.h"

#include "Channel.h"
#include "ChannelManager.h"
#include "Character.h"
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

bool Handle_CS_LOGIN_REQ(PacketSessionPtr& session, Protocol::CS_LOGIN_REQ& pkt)
{
	Protocol::SC_LOGIN_RES loginRes;
	loginRes.set_success(true);

	vector<uint32> channelIDs;
	ChannelManager::Instance().GetChannelIDs(channelIDs);
	for(const auto channelID : channelIDs)
	{
		const auto channel = ChannelManager::Instance().GetChannel(channelID);
		if (channel->GetChannelOption()._channelKey == ChannelManager::Instance().DefaultChannelID())
			continue;

		const auto& [_channelKey, 
			_channelName, 
			_maxPlayerCounts, 
			_curPlayerCounts] = channel->GetChannelOption();

		const auto resChannel = loginRes.add_channels();
		resChannel->set_channelid(_channelKey);
		resChannel->set_usercounts(_curPlayerCounts);
		resChannel->set_maxchanneluser(_maxPlayerCounts);
		for (const wchar_t c : _channelName)
			resChannel->add_channelname(c);
	}

	if(session != nullptr && session->IsConnected())
	{
		const auto sendBuffer = ClientPacketHandler::MakeSendBuffer(loginRes);
		session->Send(sendBuffer);
	}

	return true;
}

bool Handle_CS_CHANNEL_SELECT_REQ(PacketSessionPtr& session, Protocol::CS_CHANNEL_SELECT_REQ& pkt)
{
	static Atomic<uint64> playerKey = 1;
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	Protocol::SC_CHANNEL_SELECT_RES resPacket;
	// 무조건 채널입장 성공이라고 하고...
	const ChannelPtr channel = ChannelManager::Instance().GetChannel(pkt.channelindex());
	if(channel == nullptr)
	{
		resPacket.set_success(false);
		resPacket.set_channelindex(0);
		const auto sendBuffer = ClientPacketHandler::MakeSendBuffer(resPacket);
		session->Send(sendBuffer);
		session->Disconnect(L"올바르지 못한 채널 값");
		return false;
	}
	const PlayerPtr newPlayer = MakeShared<Player>();
	const uint64 newPlayerKey = playerKey.fetch_add(1);
	newPlayer->Init(newPlayerKey, static_pointer_cast<GameSession>(session));
	gameSession->SetPlayer(newPlayer);
	channel->DoAsync(&Channel::AddPlayer, newPlayer);
	

	resPacket.set_success(true);
	resPacket.set_channelindex(pkt.channelindex());

	const auto sendBuffer = ClientPacketHandler::MakeSendBuffer(resPacket);
	newPlayer->SendPacket(sendBuffer);
	return true;
}

bool Handle_CS_CHAR_LIST_REQ(PacketSessionPtr& session, Protocol::CS_CHAR_LIST_REQ& pkt)
{
	static wstring charNameBase = L"캐릭터이름_";
	static Atomic<uint64> charKey = 1;
	const GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	const PlayerPtr player = gameSession->GetPlayer();
	const auto randNum = static_cast<uint16>(rand() % 3);

	Protocol::SC_CHAR_LIST_RES resPacket;

	for(int i=0; i< randNum + 1; i++)
	{
		if (player->CanAddCharacter() == false)
			break;
		const uint64 curCharKey = charKey.fetch_add(1);
		wstring curCharName = charNameBase + to_wstring(curCharKey);
		const CharacterPtr newChar = MakeShared<Character>();
		newChar->Init(curCharKey, curCharName);
		player->AddCharacter(newChar);
		const auto packetChar = resPacket.add_characters();
		packetChar->set_id(newChar->GetCharacterKey());
		for(const wchar_t c : newChar->GetCharName())
			packetChar->add_name(c);
	}

	const auto sendBuffer = ClientPacketHandler::MakeSendBuffer(resPacket);
	player->SendPacket(sendBuffer);

	return true;
}

bool Handle_CS_CHAR_SELECT_REQ(PacketSessionPtr& session, Protocol::CS_CHAR_SELECT_REQ& pkt)
{
	const GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	auto player = gameSession->GetPlayer();
	if(player == nullptr)
	{
		player->Disconnect(L"캐릭터 요구인데,,, 이게 없을리가 없잖아");
		return false;
	}
	const auto desiredCharIndex = pkt.charindex();
	
	if(player->GetCharacterCounts() <= desiredCharIndex)
	{
		player->Disconnect(L"캐릭터 인덱스 문제");
		return false;
	}

	player->SelectCharacter(desiredCharIndex);
	const auto channel = player->GetCurrentChannel();

	const uint64 fieldCode = channel->GetStartFieldCode();
	channel->DoAsync(&Channel::EnterField, fieldCode, player);

	const auto character = player->GetSelectedCharacter();
	if(character == nullptr)
	{
		player->Disconnect(L"캐릭터가 왜 nullptr이죠,,,");
		return false;
	}

	const auto vec = character->GetCurrentPos();
	auto [x_sector, y_sector] = character->GetCurrnetSector();

	Protocol::SC_CHAR_SELECT_RES resPacket;
	resPacket.set_charindex(desiredCharIndex);
	{
		const auto pos = resPacket.add_vecs();
		pos->set_x(vec._x);
		pos->set_y(vec._y);
	}
	{
		const auto sector = resPacket.add_vecs();
		sector->set_x(x_sector);
		sector->set_y(y_sector);
	}
	const auto sendBuffer = ClientPacketHandler::MakeSendBuffer(resPacket);
	player->SendPacket(sendBuffer);
	return true;
}
bool Handle_CS_MOVE_REQ(PacketSessionPtr& session, Protocol::CS_MOVE_REQ& pkt)
{
	GameSessionPtr gameSession = static_pointer_cast<GameSession>(session);
	auto x =  pkt.curpos().x();
	auto y =pkt.curpos().y();
	auto dir = pkt.movedir();

	auto player = gameSession->GetPlayer();
	if (player == nullptr)
	{
		gameSession->Disconnect(L"플레이어가 없으면 안되는 구간입니다...");
		return false;
	}
	const auto character = player->GetSelectedCharacter();
	if(character== nullptr)
	{
		player->Disconnect(L"캐릭터가 없으면 안되는 구간입니다");
		return false;
	}

	if(player->CheckMoveSync() == false)
	{
		
	}
	const auto pos = character->GetCurrentPos();

	auto x_diff = abs(x - pos._x);
	auto y_diff = abs(y - pos._y);
	if(x_diff > 30 || y_diff >30)
	{
		// 여기서 노인정함,,, syncPacket보내야함
		player->SendSyncPacket();
	}

	return true;
}
bool Handle_CS_NORMAL_CHAT_REQ(PacketSessionPtr& session, Protocol::CS_NORMAL_CHAT_REQ& pkt)
{
	return true;
}
bool Handle_CS_MOVE_CHANNEL_REQ(PacketSessionPtr& session, Protocol::CS_MOVE_CHANNEL_REQ& pkt)
{
	return true;
}
