#include "pch.h"
#include "Character.h"

#include "GameServer.h"


Character::Character(): m_Location(){}

void Character::Init(const uint64 characterKey, const wstring& charName)
{
	BaseObject::Init(ObjectType::CHARACTER);
	m_CharacterKey = characterKey;
	m_CharName = charName;

	m_Location.init();
	m_Location.update(GameServer::Instance()->GetServerOption().m_MaxSectorSize);
}

void Character::SetMoveDirection(const Protocol::MoveDirection dir)
{
	m_Location.set_direction(dir);
}
