#pragma once
#include "BaseObject.h"

class Character : BaseObject
{
public:
	Character();
	~Character() override = default;

	void Init(const uint64 characterKey, const wstring& charName);
	void Update(uint64 deltaTick) override {}
	void SetMoveDirection(const Protocol::MoveDirection dir);

	uint64 GetCharacterKey() const { return m_CharacterKey;}
	const wstring& GetCharacterName() const { return m_CharName; }
	void SetCharacterName(const wstring& newCharName) { m_CharName = newCharName; }

	Vector2D GetCurrentPosition() const { return m_Location.get_curpos(); }
	void SetCurrentPosition(const Vector2D& pos) { m_Location.set_curpos(pos); }
	pair<uint64, uint64> GetCurrentSector() const { return m_Location.get_cur_sector(); }
private:
	uint64 m_CharacterKey = 0;
	wstring m_CharName;
	Protocol::PlayerType m_PlayerType = Protocol::PlayerType::PLAYER_TYPE_NONE;

	Location m_Location;
};
