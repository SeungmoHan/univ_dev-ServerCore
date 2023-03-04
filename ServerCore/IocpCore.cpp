#include "pch.h"
#include "IocpCore.h"
#include "IocpEvent.h"



/*--------------
	Iocp Core
--------------*/

IocpCore::IocpCore()
{
	m_IocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	ASSERT_CRASH(m_IocpHandle != INVALID_HANDLE_VALUE);
}

IocpCore::~IocpCore()
{
	CloseHandle(m_IocpHandle);
}

bool IocpCore::Register(const IocpObjectRef iocpObject) const
{
	return ::CreateIoCompletionPort(iocpObject->GetHandle(), m_IocpHandle, /*key*/ 0, 0);
}

bool IocpCore::Dispatch(const uint32 timeOutMs) const
{
	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;
	IocpEvent* iocpEvent = nullptr;

	if (::GetQueuedCompletionStatus(m_IocpHandle, OUT & numOfBytes,
		OUT &key,
		OUT reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), timeOutMs))
	{
		const IocpObjectRef iocpObject = iocpEvent->owner;
		iocpObject->Dispatch(iocpEvent, numOfBytes);
	}
	else
	{
		switch (int32 errCode = ::WSAGetLastError())
		{
		case WAIT_TIMEOUT:
			return false;
		default:
			// TODO Log
			const IocpObjectRef iocpObject = iocpEvent->owner;
			iocpObject->Dispatch(iocpEvent, numOfBytes);
			break;
		}
	}
	return true;
}
