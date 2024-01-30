#include "pch.h"
#include "ServerPacketHandler.h"
#include "ServerSession.h"

PacketHandlerFunc g_PacketHandler[UINT16_MAX];

// 직접 컨텐츠 작업자
bool Handle_INVALID(PacketSessionPtr& session, BYTE* buffer, const uint32 len)
{
	auto header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO Log...
	return false;
}

bool Handle_SC_LOGIN_RES(PacketSessionPtr& session, Protocol::SC_LOGIN_RES& pkt)
{
	ServerSessionPtr serverSession = static_pointer_cast<ServerSession>(session);
	auto channels = pkt.channels();
	const auto channelCnt = pkt.channels_size();
	ClientPlayerPtr curPlayer = DummyStructManager::Instance().GetClient(serverSession->id);
	if(curPlayer== nullptr)
	{
		serverSession->Disconnect(L"...");
		return false;
	}

	uint32 selectChannelID = 0xffff;
	for(int i=0; i<channelCnt; i++)
	{
		ptr<ClientChannelData> channelData = MakeShared<ClientChannelData>();
		auto channel = channels[i];
		for(int j=0; j< channel.channelname_size(); j++)
			channelData->channelName.push_back(channel.channelname()[j]);
		if (selectChannelID == 0xffff)
			selectChannelID = channel.channelid();
		channelData->channelID = channel.channelid();
		channelData->curChannelUserCounts = channel.usercounts(); 
		channelData->maxChannelUser = channel.maxchanneluser();
		curPlayer->_channelData.emplace(channelData->channelID, channelData);
	}

	Protocol::CS_CHANNEL_SELECT_REQ reqPacket;
	reqPacket.set_channelindex(selectChannelID);

	auto sendBuffer = ServerPacketHandler::MakeSendBuffer(reqPacket);
	session->Send(sendBuffer);

	return true;
}
bool Handle_SC_CHANNEL_SELECT_RES(PacketSessionPtr& session, Protocol::SC_CHANNEL_SELECT_RES& pkt)
{
	ServerSessionPtr serverSession = static_pointer_cast<ServerSession>(session);
	auto player = DummyStructManager::Instance().GetClient(serverSession->id);
	if (player == nullptr)
	{
		serverSession->Disconnect(L"...");
		return false;
	}

	if (pkt.success() == false)
	{
		session->Disconnect(L"채널 접속 실패");
		return false;
	}
	
	player->_selectedChannel = pkt.channelindex();

	const Protocol::CS_CHAR_LIST_REQ reqPacket;
	const auto sendBuffer = ServerPacketHandler::MakeSendBuffer(reqPacket);
	player->SendPacket(sendBuffer);
	return true;
}
bool Handle_SC_CHAR_LIST_RES(PacketSessionPtr& session, Protocol::SC_CHAR_LIST_RES& pkt)
{
	ServerSessionPtr serverSession = static_pointer_cast<ServerSession>(session);
	auto player = DummyStructManager::Instance().GetClient(serverSession->id);
	if(player == nullptr)
	{
		session->Disconnect(L"플레이어가 없을리가 없는 구간인데,,");
		return false;
	}

	int cnt = pkt.characters_size();
	for (int i = 0; i < cnt; i++)
	{
		auto data = pkt.characters()[i];

		ptr<ClientCharacterData> _character = MakeShared<ClientCharacterData>();
		_character->id = data.id();
		_character->name.reserve(data.name().size());
		for (wchar_t c : data.name())
			_character->name.push_back(c);
		_character->type = data.playertype();

		player->_characterData.emplace_back(_character);
	}

	Protocol::CS_CHAR_SELECT_REQ reqPacket;
	// 일단 무조건 0번캐릭터로,,,
	reqPacket.set_charindex(0);
	const auto buffer = ServerPacketHandler::MakeSendBuffer(reqPacket);
	player->SendPacket(buffer);

	return true;
}
bool Handle_SC_CHAR_SELECT_RES(PacketSessionPtr& session, Protocol::SC_CHAR_SELECT_RES& pkt)\
{
	const ServerSessionPtr serverSession = static_pointer_cast<ServerSession>(session);
	const auto player = DummyStructManager::Instance().GetClient(serverSession->id);
	if(player == nullptr)
	{
		session->Disconnect(L"플레이어가 없으면 안된다...");
		return false;
	}
	player->_selectedClientIndex = pkt.charindex();
	const auto pos_x = pkt.vecs()[Protocol::idx_for_cur_pos].x();
	const auto pos_y = pkt.vecs()[Protocol::idx_for_cur_pos].y();
	const auto sector_x = pkt.vecs()[Protocol::idx_for_cur_sector].x();
	const auto sector_y = pkt.vecs()[Protocol::idx_for_cur_sector].y();

	player->loc._curPos = { pos_x,pos_y };
	player->loc._sectorX = sector_x;
	player->loc._sectorY = sector_y;

	DummyStructManager::Instance().AddReadyPlayer(player);

	return true;
}
bool Handle_SC_MOVE_RES(PacketSessionPtr& session, Protocol::SC_MOVE_RES& pkt)
{
	const ServerSessionPtr serverSession = static_pointer_cast<ServerSession>(session);
	const auto client = DummyStructManager::Instance().GetClient(serverSession->id);
	if(client == nullptr)
	{
		session->Disconnect(L"클라이언트가 없다...");
		return false;
	}
	client->SetCurpos({ pkt.curpos().x(), pkt.curpos().y() });
	client->SetMoveState(pkt.movedir());
	return true;
}
bool Handle_SC_POSITION_SYNC(PacketSessionPtr& session, Protocol::SC_POSITION_SYNC& pkt)
{
	const ServerSessionPtr serverSession = static_pointer_cast<ServerSession>(session);
	const auto client = DummyStructManager::Instance().GetClient(serverSession->id);=
	client->SetCurpos({ pkt.syncposition().x(), pkt.syncposition().y() });
	return true;
}
bool Handle_SC_NORMAL_CHAT_RES(PacketSessionPtr& session, Protocol::SC_NORMAL_CHAT_RES& pkt)
{
	ServerSessionPtr serverSession = static_pointer_cast<ServerSession>(session);
	const auto client = DummyStructManager::Instance().GetClient(serverSession->id);
	if (client == nullptr)
	{
		session->Disconnect(L"클라이언트가 없을리가... 없는구간");
		return false;
	}
	// 내가 보낸 채팅이면...

	// 다른 사람이 보낸 채팅이면...
	wstring message;
	for (int i = 0; i < pkt.msg_size(); i++)
		message.push_back(pkt.msg()[i]);
	wstring name;
	for (int i = 0; i < pkt.playername_size(); i++)
		name.push_back(pkt.playername()[i]);
	client->RecvNormalChat(pkt.playerid(), message, name);
	return true;
}
bool Handle_SC_CREATE_PLAYER_CMD(PacketSessionPtr& session, Protocol::SC_CREATE_PLAYER_CMD& pkt)
{
	return true;
}
bool Handle_SC_DELETE_PLAYER_CMD(PacketSessionPtr& session, Protocol::SC_DELETE_PLAYER_CMD& pkt)
{
	return true;
}

bool Handle_SC_MOVE_CHANNEL_RES(PacketSessionPtr& session, Protocol::SC_MOVE_CHANNEL_RES& pkt)
{
	return true;
}
