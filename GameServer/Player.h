#pragma once
#include "BaseObject.h"


class Character;
class Field;
class Room;

class Player : public BaseObject
{
public:
	enum PlayerMoveDirection
	{
		None = 0, Left, Right, Up, Down,
	};
	Player() = default;
	~Player() override = default;
	void Init(const uint64 playerId,
	          const GameSessionPtr& ownerSession);

	void SendPacket(const SendBufferPtr& sendBuffer) const;
	void Disconnect(const wstring& reason);

	void OnDisconnected();

	uint64 GetPlayerKey() const { return m_PlayerGuid; }

	ptr<Room> SetCurrentRoom(const ptr<Room>& gameRoom);
	ptr<Room> GetCurrentRoom() const;

	ChannelPtr SetCurrentChannel(const ChannelPtr& channel);
	ChannelPtr GetCurrentChannel() const;

	ptr<Field> SetCurrentField(const ptr<Field>& field);
	ptr<Field> GetCurrentField() const;

	void Update(uint64 deltaTick) override;

	GameSessionPtr GetOwnerSession() const { return m_OwnerSession; }

	void SelectCharacter(const uint64 characterIndex);
	ptr<Character> GetSelectedCharacter() const;

	size_t GetCharacterCounts() const { return m_CharacterList.size(); }

	bool CanAddCharacter() const;
	void AddCharacter(const ptr<Character> character);

	void OnEnterChannel(ptr<Channel> channel);
	void OnEnterRoom(ptr<Room> room);
	void OnEnterField(ptr<Field> field);


	bool CheckMoveSync(const Vector2D& vec);

	void ChangeMoveStatus(const Protocol::MoveDirection dir, const Vector2D curPos);

	void ResetPlayer();

	void SendSyncPacket();
private:

	void Reset();
	// 플레이어 정보
	uint64						m_PlayerGuid		= 0;
	GameSessionPtr				m_OwnerSession		= nullptr;
	ptr<Channel>				m_CurrentChannel	= nullptr;
	ptr<Room>					m_Room				= nullptr;
	ptr<Field>					m_Field				= nullptr;

	ptr<Character>				m_SelectedCharacter = nullptr;
	vector<ptr<Character>>		m_CharacterList;
};

using PlayerPtr = ptr<Player>;