#include "pch.h"
#include "ClientPlayer.h"
#include "Protocol.pb.h"
#include "ServerPacketHandler.h"

void ClientPlayer::SendPacket(const SendBufferPtr sendBuffer) const
{
	_ownerSession->Send(sendBuffer);
}

void ClientPlayer::ChangeState()
{
	_moveState = static_cast<Protocol::MoveDirection>(rand() % 5);

	Protocol::CS_MOVE_REQ movePacket;

	movePacket.set_movedir(_moveState);
	Protocol::Packet_Vector vec;
	vec.set_x(loc._curPos._x);
	vec.set_y(loc._curPos._y);
	movePacket.set_allocated_curpos(&vec);

	const auto sendBuffer= ServerPacketHandler::MakeSendBuffer(movePacket);
	SendPacket(sendBuffer);
}

void ClientPlayer::SetCurpos(const Vector2D& vec)
{
	loc._curPos = vec;
}

void ClientPlayer::SendNormalChat()
{
	if (_chatState == ChatState::Sended)
		return;
	_chatState = ChatState::Sended;
	static wstring text = L"안녕하시옵니까?~__";
	static Atomic<uint64> chatCounts = 0;

	const uint64 cur = chatCounts.fetch_add(1);

	const wstring sendMessage = text + to_wstring(cur);

	Protocol::CS_NORMAL_CHAT_REQ chatPacket;
	for (const auto c : sendMessage)
		chatPacket.add_msg(c);

	const auto sendBuffer = ServerPacketHandler::MakeSendBuffer(chatPacket);
	SendPacket(sendBuffer);

}

void ClientPlayer::RecvNormalChat(uint64 playerID, const wstring& message, const wstring& name)
{
	// 내가 보낸 메시지였다면
	if(playerID == GetSelectedCharKey())
	{
		// 일단은 상태만 원상복구 시키고 나가자...
		if (_chatState == ChatState::CanSend)
			return;
		_chatState = ChatState::CanSend;
	}
	else
	{
		// 일단 다른사람이 보낸거 체크할 그건없음...
		// 추후에 내 주변에 이 플레이어가 있어야하는지 검사하는 로직에서 검증할 예정
	}

}

void ClientPlayer::SetMoveState(const Protocol::MoveDirection dir)
{
	_moveState = dir;
}

void ClientPlayer::Update()
{
	if (_finished_to_set.load() == false)
		return;
	if(const uint64 curTick = GetTickCount64(); curTick >= nextUpdateTick)
	{
		nextUpdateTick += 1000;
		if(const uint32 randVal = rand() % 10; randVal <= 7)
			return;
		ChangeState();
		SendNormalChat();
	}
}

bool ClientPlayer::IsPlayerNearby(const uint64 key)
{
	const auto itr = _otherUserData.find(key);
	if (itr == _otherUserData.end())
		return false;
	return true;
}

bool ClientPlayer::CheckDuplicateCharacterSpawn(const uint64 key)
{
	return IsPlayerNearby(key) == true;
}

bool ClientPlayer::InsertNearbyCharacter(ptr<ClientCharacterData> charData)
{
	if (CheckDuplicateCharacterSpawn(charData->id) == true)
		return false;

	_otherUserData.emplace(charData->id, charData);
}

bool ClientPlayer::RemoveNearbyCharacter(const uint64 key)
{
	if (IsPlayerNearby(key) == false)
		return false;

	_otherUserData.erase(key);
	return true;
}
