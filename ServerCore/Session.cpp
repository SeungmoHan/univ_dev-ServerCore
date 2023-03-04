#include "pch.h"
#include "Session.h"
#include "SocketUtils.h"
#include "Service.h"




/*----------------
	Session
----------------*/
Session::Session() : m_RecvBuffer(BUFFER_SIZE)
{
	m_Socket = SocketUtils::CreateSocket();
}

Session::~Session()
{
	SocketUtils::Close(m_Socket);
}


void Session::Send(SendBufferRef buffer)
{
	WRITE_LOCK;

	m_SendQueue.push(buffer);

	if (m_SendRegistered.exchange(true) == false)
	{
		RegisterSend();
	}
	
}

bool Session::Connect()
{
	return RegisterConnect();
}

void Session::Disconnect(const WCHAR* reason)
{
	if (m_Connected.exchange(false) == false)
		return;

	//   [2/25/2023 SeungmoHan] temp
	wcout << L"Disconnect " << reason << endl;

	OnDisconnected();
	GetService()->ReleaseSession(GetSessionRef());

	RegisterDisconnect();
}
HANDLE Session::GetHandle()
{
	return reinterpret_cast<HANDLE>(m_Socket);
}

void Session::Dispatch(IocpEvent* iocpEvent, int32 numberOfBytes)
{
	//TODO
	switch (iocpEvent->eventType)
	{
	case EventType::Connect:
		ProcessConnect();
		break;
	case EventType::Disconnect:
		ProcessDisconnect();
		break;
	case EventType::Recv:
		ProcessRecv(numberOfBytes);
		break;
	case EventType::Send:
		ProcessSend(numberOfBytes);
		break;
	default:
		break;
	}
}

bool Session::RegisterConnect()
{
	if (IsConnected())
		return false;

	if (GetService()->GetServiceType() != ServiceType::Client)
		return false;

	if (SocketUtils::SetReuseAddress(m_Socket, true) == false)
		return false;

	if (SocketUtils::BindAnyAddress(m_Socket, 0) == false)
		return false;

	m_ConnectEvent.Init();
	
	m_ConnectEvent.owner = shared_from_this();

	DWORD numOfBytes = 0;
	sockaddr_in addr = GetService()->GetNetAddress().GetSockAddr();
	if (false == SocketUtils::ConnectEx(m_Socket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr), nullptr, 0, &numOfBytes, &m_ConnectEvent))
	{
		int32 errCode = WSAGetLastError();
		if (errCode != WSA_IO_PENDING)
		{
			m_ConnectEvent.owner = nullptr;
			return false;
		}
	}
	return true;
}

bool Session::RegisterDisconnect()
{
	m_DisconnectEvent.Init();
	m_DisconnectEvent.owner = shared_from_this();

	if (false == SocketUtils::DisconnectEx(m_Socket, &m_DisconnectEvent, TF_REUSE_SOCKET, 0))
	{
		int32 errCode = WSAGetLastError();
		if (errCode != WSA_IO_PENDING)
		{
			m_DisconnectEvent.owner = nullptr; // Release Ref
			return false;
		}
	}
	return true;
}

void Session::RegisterRecv()
{
	if (IsConnected() == false)
		return;

	WSABUF buf;
	//  [2/19/2023 SeungmoHan] temp
	buf.buf = reinterpret_cast<char*>(m_RecvBuffer.WritePos());
	buf.len = m_RecvBuffer.FreeSize();

	m_RecvEvent.Init();
	m_RecvEvent.owner = shared_from_this(); // Add Ref

	DWORD numOfBytes = 0;
	DWORD flag = 0;

	if (SOCKET_ERROR == ::WSARecv(m_Socket, &buf, 1, OUT &numOfBytes, OUT &flag, &m_RecvEvent, nullptr))
	{
		int32 errCode = WSAGetLastError();
		if (errCode != WSA_IO_PENDING)
		{
			// TODO Log추가 + 에러 처리
			ErrorHandler(errCode);
			m_RecvEvent.owner = nullptr; // Release Ref
		}
	}
}

void Session::RegisterSend()
{
	if (IsConnected() == false)
		return;

	m_SendEvent.Init();
	m_SendEvent.owner = shared_from_this();

	{
		WRITE_LOCK;

		uint32 writeSize = 0;
		while(!m_SendQueue.empty())
		{
			auto sendBuffer = m_SendQueue.front();

			writeSize += sendBuffer->WriteSize();

			m_SendEvent.sendBuffers.push_back(sendBuffer);
			m_SendQueue.pop();
		}
	}

	Vector<WSABUF> bufs;
	bufs.reserve(m_SendEvent.sendBuffers.size());
	for (auto sendBuffer : m_SendEvent.sendBuffers)
	{
		WSABUF buf;
		buf.buf = reinterpret_cast<char*>(sendBuffer->Buffer());
		buf.len = static_cast<ULONG>(sendBuffer->WriteSize());
		bufs.push_back(buf);
	}

	DWORD numOfBytes = 0;
	if (SOCKET_ERROR == WSASend(m_Socket, bufs.data(), static_cast<DWORD>(bufs.size()), OUT & numOfBytes, 0, &m_SendEvent, nullptr))
	{
		int errCode = WSAGetLastError();
		if (errCode != WSA_IO_PENDING)
		{
			ErrorHandler(errCode);
			m_SendEvent.owner = nullptr;
			m_SendEvent.sendBuffers.clear();
			m_SendRegistered.store(false);
		}
	}
}

void Session::ProcessConnect()
{
	m_ConnectEvent.owner = nullptr; // Release Ref
	m_Connected.store(true);

	GetService()->AddSession(GetSessionRef());

	OnConnect();

	RegisterRecv();
}

void Session::ProcessDisconnect()
{
	m_DisconnectEvent.owner = nullptr;
}

void Session::ProcessRecv(int32 numOfBytes)
{
	m_RecvEvent.owner = nullptr; // Release Ref
	if (numOfBytes == 0)
	{
		Disconnect(L"RecvBytes 0");
		return;
	}
	if (m_RecvBuffer.OnWrite(numOfBytes) == false)
	{
		Disconnect(L"OnWrite Error");
		return;
	}

	uint32 dataSize = m_RecvBuffer.DataSize();

	int32 processLen = OnRecv(m_RecvBuffer.ReadPos(), dataSize);
	if (processLen < 0 || dataSize < processLen || m_RecvBuffer.OnRead(processLen) == false)
	{
		Disconnect(L"OnRead Error");
		return;
	}

	m_RecvBuffer.Clean();

	RegisterRecv();
}

void Session::ProcessSend(int32 numOfBytes)
{
	m_SendEvent.owner = nullptr; // Release Ref
	m_SendEvent.sendBuffers.clear(); // Release Ref
	if (numOfBytes == 0)
	{
		Disconnect(L"Send 0");
	}

	OnSend(numOfBytes);

	WRITE_LOCK;
	if (m_SendQueue.empty())
		m_SendRegistered.store(false);
	else
		RegisterSend();
}

void Session::ErrorHandler(int32 errCode)
{
	switch (errCode)
	{
	case WSAECONNABORTED:
	case WSAECONNRESET:
		Disconnect(L"HandleError");
		break;
	default:
		// TODO Log
		std::cout << "Handle Error : " << errCode << endl;
	}
}
