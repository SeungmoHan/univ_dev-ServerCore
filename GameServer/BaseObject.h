#pragma once
#include "JobSerializer.h"


enum ObjectType
{
	NONE,
	PLAYER,
	CHARACTER,
	NPC,
	MONSTER,
};

class BaseObject : public JobSerializer
{
protected:
	inline static Atomic<uint64> ObjectKeyGenerator = 1;
public:
	~BaseObject() override = default;
	BaseObject() = default;

	virtual void Init(ObjectType objType);
	virtual void Update(uint64 deltaTick) = 0;


private:
	uint64 m_ObjectKey = 0;
	ObjectType m_ObjectType;
};
