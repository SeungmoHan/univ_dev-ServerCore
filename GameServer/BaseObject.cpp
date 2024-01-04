#include "pch.h"
#include "BaseObject.h"

void BaseObject::Init(uint64 objKey, ObjectType objType)
{
	m_ObjectKey = objKey;
	m_ObjectType = objType;
}
