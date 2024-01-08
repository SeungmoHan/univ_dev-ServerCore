#pragma once
#include "BaseObject.h"


class Room;

class Player : public BaseObject
{
public:
	Player() = default;
	~Player() override = default;
	void Init(const uint64 playerId,
	          const string& name,
	          const Protocol::PlayerType type,
	          const GameSessionPtr& ownerSession);

	void SendPacket(const SendBufferPtr& sendBuffer) const;

	uint64 GetPlayerGuid() const { return m_PlayerGuid; }
	const string& GetPlayerName() const { return m_Name; }

	ptr<Room> SetCurrentRoom(const ptr<Room>& gameRoom);
	ptr<Room> GetCurrentRoom() const;

	ChannelPtr SetCurrentChannel(const ChannelPtr& channel);
	ChannelPtr GetCurrentChannel() const;

	void Update(uint64 deltaTick) override;

	GameSessionPtr GetOwnerSession() const { return m_OwnerSession; }
	

private:
	uint64						m_PlayerGuid = 0;
	string						m_Name;
	Protocol::PlayerType		m_Type = Protocol::PLAYER_TYPE_NONE;
	GameSessionPtr				m_OwnerSession;
	ChannelPtr					m_CurrentChannel;
	weak_ptr<Room>				m_Room;
};

using PlayerPtr = ptr<Player>;