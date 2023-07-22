#include "pch.h"
#include "ClientPacketHandler.h"
#include "Player.h"
#include "Room.h"
#include "GameSession.h"

PacketHandlerFunc g_PacketHandler[UINT16_MAX];

// 직접 컨텐츠 작업자
bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, const uint32 len)
{
	auto header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO Log...
	return false;
}

bool Handle_CS_LOGIN(PacketSessionRef& session, Protocol::CS_LOGIN& pkt)
{
	const GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

	// TODO validation

	Protocol::SC_LOGIN loginPacket;
	loginPacket.set_success(true);


	// DB에서 Player정보 긁어오는 내용
	// 긁어온 정보를 GameSession에 저장(메모리상에 저장)
	static Atomic<uint64> idGenerator = 1;
	{
		const auto player = loginPacket.add_players();
		player->set_name(u8"DB에서 긁어온이름1");
		player->set_playertype(Protocol::PLAYER_TYPE_KNIGHT);

		const PlayerRef playerRef = MakeShared<Player>();
		playerRef->m_PlayerId = idGenerator++;
		playerRef->m_Name = player->name();
		playerRef->m_Type = player->playertype();
		playerRef->m_OwnerSession = gameSession;

		gameSession->m_Players.push_back(playerRef);
	}

	{
		const auto player = loginPacket.add_players();
		player->set_name(u8"DB에서 긁어온이름2");
		player->set_playertype(Protocol::PLAYER_TYPE_KNIGHT);

		const PlayerRef playerRef = MakeShared<Player>();
		playerRef->m_PlayerId = idGenerator++;
		playerRef->m_Name = player->name();
		playerRef->m_Type = player->playertype();
		playerRef->m_OwnerSession = gameSession;

		gameSession->m_Players.push_back(playerRef);
	}

	const auto sendBuffer = ClientPacketHandler::MakeSendBuffer(loginPacket);
	session->Send(sendBuffer);

	return false;
}

bool Handle_CS_ENTER_GAME(PacketSessionRef& session, Protocol::CS_ENTER_GAME& pkt)
{
	const GameSessionRef gameSession = static_pointer_cast<GameSession>(session);

	const uint64 index = pkt.playerindex();
	//TODO validation
	const auto player = gameSession->m_Players[index];
	g_Room->PushJob(&Room::Enter, player);

	Protocol::SC_ENTER_GAME enterGamePacket;
	enterGamePacket.set_success(true);

	const auto sendBuffer = ClientPacketHandler::MakeSendBuffer(enterGamePacket);
	player->m_OwnerSession->Send(sendBuffer);

	return true;
}

bool Handle_CS_NORMAL_CHAT(PacketSessionRef& session, Protocol::CS_NORMAL_CHAT& pkt)
{

	std::cout << pkt.msg() << endl;

	Protocol::SC_NORMAL_CHAT chatPacket;
	chatPacket.set_msg(pkt.msg());


	const auto sendBuffer = ClientPacketHandler::MakeSendBuffer(chatPacket);
	g_Room->PushJob(&Room::Broadcast, sendBuffer);

	return true;
}


