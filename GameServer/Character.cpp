#include "pch.h"
#include "Character.h"

#include "GameServer.h"


void Character::Init(const uint64 characterKey, const wstring& charName)
{
	BaseObject::Init(ObjectType::CHARACTER);
	m_CharacterKey = characterKey;
	m_CharName = charName;

	m_Location.init();
	m_Location.update(GameServer::Instance()->GetServerOption().m_MaxSectorSize);
}
