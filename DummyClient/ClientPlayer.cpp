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
	vec.set_x(curPos._x);
	vec.set_y(curPos._y);
	movePacket.set_allocated_curpos(&vec);

	const auto sendBuffer= ServerPacketHandler::MakeSendBuffer(movePacket);
	SendPacket(sendBuffer);
}

void ClientPlayer::SendNormalChat()
{
	static wstring text = L"안녕하시옵니까?~__";
	static Atomic<uint64> chatCounts = 0;

	const uint64 cur = chatCounts.fetch_add(1);

	wstring sendMessage = text + to_wstring(cur);

	Protocol::CS_NORMAL_CHAT_REQ chatPacket;
	for (const auto c : sendMessage)
		chatPacket.add_msg(c);

	const auto sendBuffer = ServerPacketHandler::MakeSendBuffer(chatPacket);
	SendPacket(sendBuffer);

}

void ClientPlayer::Update()
{
	if (_finished_to_set.load() == false)
		return;
	uint64 curTick = GetTickCount64();
	if(curTick >= nextUpdateTick)
	{
		nextUpdateTick += 1000;
		if(const uint32 randVal = rand() % 10; randVal <= 7)
			return;
		ChangeState();
		SendNormalChat();
	}

	
}
