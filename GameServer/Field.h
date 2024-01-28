#pragma once
#include "BaseObject.h"
#include "JobSerializer.h"

class Field : public JobSerializer
{
public:

	void Init();

	void AddPlayer(CharacterPtr character);
	void LeavePlayer(CharacterPtr character);

	bool Update(uint64 deltaTick);


	uint64 GetFieldCode() const;
	CharacterPtr GetPlayer(const uint64 characterKey);

private:
	uint64 m_FieldCode;

	unordered_map<uint64, ptr<BaseObject>> m_NPCMap;

	unordered_map<uint64, CharacterPtr> m_CharacterMap;
};


using FieldPtr = ptr<Field>;