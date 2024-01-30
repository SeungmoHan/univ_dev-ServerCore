#pragma once
#include "ServerSession.h"
#include "Structs.h"
#include "TempStruct.h"

class ClientPlayer 
{
public:

	enum class ChatState
	{
		CanSend, Sended,
	};

	void SendPacket(const SendBufferPtr sendBuffer) const;
	void ChangeState();
	void SetCurpos(const Vector2D& vec);

	void SendNormalChat();
	void RecvNormalChat(uint64 playerID, const wstring& message, const wstring& name);

	void SetMoveState(Protocol::MoveDirection dir);
	void Update();

	uint64 GetSelectedCharKey() const { return _characterData[_selectedClientIndex]->id; }

	uint64 _key = 0;
	Atomic<bool> _finished_to_set = false;

	Location loc;

	ptr<ServerSession> _ownerSession;
	uint32 _selectedChannel;
	HashMap<uint32, ptr<ClientChannelData>> _channelData;

	uint64 _selectedClientIndex;
	uint64 _charKey;
	Vector<ptr<ClientCharacterData>> _characterData;

	Vector2D _curPos;

	Protocol::MoveDirection _moveState;
	ChatState _chatState;

	uint64 nextUpdateTick = 0;
};

