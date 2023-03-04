#include "pch.h"
#include "IocpEvent.h"

IocpEvent::IocpEvent(const EventType type) : _OVERLAPPED(), eventType(type)
{
	Init();
}

void IocpEvent::Init()
{
	OVERLAPPED::hEvent = 0;
	OVERLAPPED::Internal= 0;
	OVERLAPPED::InternalHigh = 0;
	OVERLAPPED::Offset	 = 0;
	OVERLAPPED::OffsetHigh = 0;
}
