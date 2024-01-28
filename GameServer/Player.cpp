#include "pch.h"
#include "Player.h"

#include "Channel.h"
#include "Character.h"
#include "ClientPacketHandler.h"
#include "Field.h"
#include "GameServer.h"
#include "GameSession.h"
#include "Protocol.pb.h"
#include "Room.h"

void Player::Init(const uint64 playerId, const GameSessionPtr& ownerSession)
{
	Reset();
	BaseObject::Init(ObjectType::PLAYER);
	m_OwnerSession = ownerSession;
	m_PlayerGuid = playerId;
}

void Player::SendPacket(const SendBufferPtr& sendBuffer) const
{
	m_OwnerSession->Send(sendBuffer);
}

void Player::Disconnect(const wstring& reason)
{
	m_OwnerSession->Disconnect(reason.c_str());
}

void Player::OnDisconnected()
{
	// Field::LeavePlayer는 Channel에서 leave시켜주니까 할필요 X
	if(m_CurrentChannel) m_CurrentChannel->DoAsync<Channel, void>(&Channel::RemovePlayer, GetPlayerGuid());
	if (m_Room) m_Room->DoAsync<Room, void>(&Room::Leave, GetPlayerGuid());
	Reset();
}

ptr<Room> Player::SetCurrentRoom(const ptr<Room>& gameRoom)
{
	m_Room = gameRoom;
	return m_Room;
}

ptr<Room> Player::GetCurrentRoom() const
{
	return m_Room;
}

ChannelPtr Player::SetCurrentChannel(const ChannelPtr& channel)
{
	return m_CurrentChannel = channel;
}

ChannelPtr Player::GetCurrentChannel() const
{
	return m_CurrentChannel;
}

ptr<Field> Player::SetCurrentField(const ptr<Field>& field)
{
	return m_Field = field;
}

ptr<Field> Player::GetCurrentField() const
{
	return m_Field;
}

void Player::Update(uint64 deltaTick)
{
	//TODO 플레이어 움직이는거나,,, 이런거 여기서 할예정임
	// 다만 State 변경 같은건 패킷에서 DoAsync를 이용해서 수정할거
}

void Player::SelectCharacter(const uint64 characterIndex)
{
	if (characterIndex >= m_CharacterList.size())
		GetOwnerSession()->Disconnect(L"캐릭터 인덱스가 잘못되었는데..?");

	m_SelectedCharacter = m_CharacterList[characterIndex];
}

ptr<Character> Player::GetSelectedCharacter() const
{
	return m_SelectedCharacter;
}

bool Player::CanAddCharacter() const
{
	return GameServer::Instance()->GetServerOption().m_MaxCharacterPerPlayer < m_CharacterList.size();
}

void Player::AddCharacter(const ptr<Character> character)
{
	
	if (CanAddCharacter())
		m_CharacterList.emplace_back(character);
}

void Player::OnEnterChannel(ptr<Channel> channel)
{
	m_CurrentChannel = channel;
}

void Player::OnEnterRoom(ptr<Room> room)
{
	m_Room = room;
}

void Player::OnEnterField(ptr<Field> field)
{
	m_Field = field;
}

bool Player::CheckMoveSync(const Vector2D& vec)
{
	const auto character = GetSelectedCharacter();
	if(character == nullptr)
	{
		Disconnect(L"캐릭터가 여기서 없으면 안되죵~");
		return false;
	}
	const auto charPos = character->GetCurrentPos();
	const auto x_diff = abs(vec._x - charPos._x);
	const auto y_diff = abs(vec._y - charPos._y);
	if (x_diff > 30 || y_diff > 30)
	{
		// 여기서 노인정함,,, syncPacket보내야함
		// sync 보내고,,, true를 보내자 그냥 일단은
		SendSyncPacket();
	}

	// 일단은 다 true
	return true;
}

void Player::ResetPlayer()
{
	m_OwnerSession = nullptr;
	m_Room = nullptr;
	m_Field = nullptr;
	m_SelectedCharacter = nullptr;
	m_CurrentChannel = nullptr;
	m_CharacterList.clear();
}

void Player::SendSyncPacket()
{
	const auto character = m_SelectedCharacter;
	if(character == nullptr)
	{
		Disconnect(L"캐릭터가 없으면 안되지...");
		return;
	}
	auto pos = character->GetCurrentPos();

	Protocol::SC_POSITION_SYNC syncPacket;
	Protocol::Packet_Vector vec;
	vec.set_x(pos._x); vec.set_y(pos._y);
	syncPacket.set_allocated_syncposition(&vec);

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(syncPacket);
	SendPacket(sendBuffer);
}

void Player::Reset()
{
	m_OwnerSession = nullptr;
	m_Room = nullptr;
	m_Field = nullptr;
	m_SelectedCharacter = nullptr;
	m_CurrentChannel = nullptr;
	m_CharacterList.clear();
}
