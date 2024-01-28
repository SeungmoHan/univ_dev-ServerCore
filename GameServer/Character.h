#pragma once
#include "BaseObject.h"

class Character : BaseObject
{
public:
	void Init(const uint64 characterKey, const wstring& charName);
	virtual void Update(uint64 deltaTick){};

	uint64 GetCharacterKey() const { return m_CharacterKey;}
	const wstring& GetCharName() const { return m_CharName; }
	void SetCharName(const wstring& newCharName) { m_CharName = newCharName; }

	Vector2D GetCurrentPos() const { return m_Location.get_curpos(); }
	pair<uint64, uint64> GetCurrnetSector() const { return m_Location.get_cur_sector(); }
private:
	uint64 m_CharacterKey = 0;
	wstring m_CharName;
	Protocol::PlayerType m_PlayerType = Protocol::PlayerType::PLAYER_TYPE_NONE;

	Location m_Location;
};
