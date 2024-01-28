#include "pch.h"
#include "BaseObject.h"

void BaseObject::Init(ObjectType objType)
{
	m_ObjectKey = ObjectKeyGenerator.fetch_add(1);
	m_ObjectType = objType;
}
