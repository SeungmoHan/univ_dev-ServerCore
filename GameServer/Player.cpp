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
	//TODO �÷��̾� �����̴°ų�,,, �̷��� ���⼭ �ҿ�����
	// �ٸ� State ���� ������ ��Ŷ���� DoAsync�� �̿��ؼ� �����Ұ�
}
