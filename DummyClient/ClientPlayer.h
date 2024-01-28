#pragma once
#include "ServerSession.h"
#include "Structs.h"
#include "TempStruct.h"

class ClientPlayer 
{
public:

	enum class ChatState
	{
		None, Send, RecvWait, Recved,
	};

	void SendPacket(const SendBufferPtr sendBuffer) const;
	void ChangeState();

	void SendNormalChat();
	void Update();

	uint64 _key = 0;
	Atomic<bool> _finished_to_set = false;

	Location loc;

	ptr<ServerSession> _ownerSession;
	uint32 _selectedChannel;
	HashMap<uint32, ptr<ClientChannelData>> _channelData;

	uint64 _selectedClientIndex;
	Vector<ptr<ClientCharacterData>> _characterData;

	Vector2D curPos;

	Protocol::MoveDirection _moveState;
	ChatState _chatState;

	uint64 nextUpdateTick = 0;
};

