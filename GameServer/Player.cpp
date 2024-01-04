#include "pch.h"
#include "Player.h"
#include "GameSession.h"
#include "Room.h"

void Player::Init(const uint64 playerId, const string& name, const Protocol::PlayerType playerType, const GameSessionPtr& ownerSession)
{
	BaseObject::Init(ObjectKeyGenerator.fetch_add(1), ObjectType::PLAYER);
	m_OwnerSession = ownerSession;
	m_PlayerGuid = playerId;
	m_Name = name;
	m_Type = playerType;
}

void Player::SendPacket(const SendBufferPtr& sendBuffer) const
{
	m_OwnerSession->Send(sendBuffer);
}

ptr<Room> Player::SetCurrentRoom(const ptr<Room>& gameRoom)
{
	m_Room = gameRoom;
	return m_Room.lock();
}

ptr<Room> Player::GetCurrentRoom() const
{
	return m_Room.lock();
}

void Player::Update()
{
	//TODO 플레이어 움직이는거나,,, 이런거 여기서 할예정임
	// 다만 State 변경 같은건 패킷에서 DoAsync를 이용해서 수정할거
}
