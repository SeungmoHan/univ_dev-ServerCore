#include "pch.h"
#include "Field.h"

#include "Character.h"
#include "Player.h"

void Field::Init()
{
	static Atomic<uint64> FieldCodeGenerator = 1;

	uint64 curFieldCode = FieldCodeGenerator.fetch_add(1);
	m_FieldCode = curFieldCode;
}

void Field::AddPlayer(CharacterPtr character)
{
	if (character == nullptr)
		return;
	m_CharacterMap.emplace(character->GetCharacterKey(), character);
	//character->OnEnterField();
}

void Field::LeavePlayer(CharacterPtr character)
{
	if (character == nullptr)
		return;

	auto itr = m_CharacterMap.find(character->GetCharacterKey());
	if(itr == m_CharacterMap.end())
		return;

	m_CharacterMap.erase(character->GetCharacterKey());
}

bool Field::Update(const uint64 deltaTick)
{
	for(const auto& [npcKey, npc] : m_NPCMap)
	{
		npc->Update(deltaTick);
	}
	return true;
}

uint64 Field::GetFieldCode() const
{
	return m_FieldCode;
}

CharacterPtr Field::GetPlayer(const uint64 characterKey)
{
	const auto itr = m_CharacterMap.find(characterKey);
	if (itr == m_CharacterMap.end())
		return nullptr;
	return itr->second;
}
