#include "pch.h"
#include "Listener.h"
#include "SocketUtils.h"
#include "IocpEvent.h"
#include "Session.h"
#include "Service.h"

/*----------------
	Listener
----------------*/
Listener::~Listener()
{
	SocketUtils::Close(m_Socket);

	for (AcceptEvent* acceptEvent : m_AcceptEvents)
	{
		// TODO

		xdelete(acceptEvent);
	}
}

bool Listener::StartAccept(ServerServiceRef service)
{
	m_Service = service;
	if (m_Service == nullptr)
		return false;

	m_Socket = SocketUtils::CreateSocket();
	if (m_Socket == INVALID_SOCKET)
		return false;

	if (service->GetIocpCore()->Register(shared_from_this()) == false)
		return false;

	if (SocketUtils::SetReuseAddress(m_Socket, true) == false)
		return false;

	if (SocketUtils::SetLinger(m_Socket, 0, 0) == false)
		return false;

	if (SocketUtils::Bind(m_Socket, service->GetNetAddress()) == false)
		return false;

	if (SocketUtils::Listen(m_Socket) == false)
		return false;

	//const int32 acceptCount = _service->GetMaxSessionCount();
	const int32 acceptCount = 1;
	for (int32 i = 0; i < acceptCount; i++)
	{
		AcceptEvent* acceptEvent = xnew<AcceptEvent>();
		acceptEvent->owner = shared_from_this();
		m_AcceptEvents.push_back(acceptEvent);
		RegisterAccept(acceptEvent);
	}


	return true;
}

void Listener::CloseSocket()
{
	SocketUtils::Close(m_Socket);
}

HANDLE Listener::GetHandle()
{
	return reinterpret_cast<HANDLE>(m_Socket);
}

void Listener::Dispatch(IocpEvent* iocpEvent, int32 numberOfBytes)
{
	ASSERT_CRASH(iocpEvent->eventType == EventType::Accept);

	AcceptEvent* acceptEvent = static_cast<AcceptEvent*>(iocpEvent);
	ProcessAccept(acceptEvent);
}

void Listener::RegisterAccept(AcceptEvent* acceptEvent)
{
	SessionRef session = m_Service->CreateSession();

	acceptEvent->Init();
	acceptEvent->session = session;

	SOCKET clientSocket = SocketUtils::CreateSocket();

	DWORD bytesRecieved = 0;
	if (false == SocketUtils::AcceptEx(m_Socket, session->GetSocket(), session->m_RecvBuffer.WritePos(), 0,
		sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16,
		OUT &bytesRecieved, static_cast<LPOVERLAPPED>(acceptEvent)))
	{
		const int32 errCode = WSAGetLastError();
		if (errCode != WSA_IO_PENDING)
		{
			RegisterAccept(acceptEvent);
		}
	}
}

void Listener::ProcessAccept(AcceptEvent* acceptEvent)
{
	SessionRef session = acceptEvent->session;

	if (!SocketUtils::SetUpdateAcceptSocket(session->GetSocket(), m_Socket))
	{
		RegisterAccept(acceptEvent);
		return;
	}


	sockaddr_in addr;
	int32 addrSize = sizeof(addr);

	if (SOCKET_ERROR == getpeername(session->GetSocket(), OUT reinterpret_cast<sockaddr*>(&addr), &addrSize))
	{
		RegisterAccept(acceptEvent);
		return;
	}

	session->SetNetAddress(NetAddress(addr));
	session->ProcessConnect();

	cout << "Client Connected" << endl;
	RegisterAccept(acceptEvent);
}
