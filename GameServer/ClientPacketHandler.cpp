#include "pch.h"
#include "ClientPacketHandler.h"
#include "GameRoomManager.h"
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
	loginPacket.set_success(true);


	// DB에서 Player정보 긁어오는 내용
	// 긁어온 정보를 GameSession에 저장(메모리상에 저장)
	static Atomic<uint64> idGenerator = 1;
	string temp = u8"Test";
	{
		const auto player = loginPacket.add_players();
		string charName = temp + to_string(idGenerator);
		player->set_name(charName);
		player->set_playertype(Protocol::PLAYER_TYPE_KNIGHT);

		const PlayerPtr playerRef = MakeShared<Player>();
		playerRef->Init(idGenerator, player->name(), player->playertype(), gameSession);

		player->set_id(playerRef->GetPlayerGuid());
		player->set_name(playerRef->GetPlayerName());
		gameSession->AddPlayer(playerRef);
		++idGenerator;
	}

	{
		const auto player = loginPacket.add_players();
		string charName = temp + to_string(idGenerator);
		player->set_name(charName);
		player->set_playertype(Protocol::PLAYER_TYPE_KNIGHT);

		const PlayerPtr playerRef = MakeShared<Player>();
		playerRef->Init(idGenerator, player->name(), player->playertype(), gameSession);
		
		player->set_id(playerRef->GetPlayerGuid());
		player->set_name(playerRef->GetPlayerName());
		gameSession->AddPlayer(playerRef);
		++idGenerator;
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


