#include "pch.h"
#include "SocketUtils.h"
#include "NetworkAddress.h"

/*--------------------
	SOCKET Util
--------------------*/


LPFN_CONNECTEX		SocketUtils::ConnectEx = nullptr;
LPFN_DISCONNECTEX	SocketUtils::DisconnectEx = nullptr;
LPFN_ACCEPTEX		SocketUtils::AcceptEx = nullptr;

void SocketUtils::Init()
{
	WSADATA data;
	ASSERT_CRASH(WSAStartup(MAKEWORD(2, 2), &data) == 0);

	SOCKET dummySocket = CreateSocket();
	ASSERT_CRASH(BindIOCPCallback(dummySocket, WSAID_CONNECTEX, reinterpret_cast<LPVOID*>(&ConnectEx)) == true);
	ASSERT_CRASH(BindIOCPCallback(dummySocket, WSAID_DISCONNECTEX, reinterpret_cast<LPVOID*>(&DisconnectEx)) == true);
	ASSERT_CRASH(BindIOCPCallback(dummySocket, WSAID_ACCEPTEX, reinterpret_cast<LPVOID*>(&AcceptEx)) == true);
	CloseSocket(dummySocket);
}

void SocketUtils::Clear()
{
	WSACleanup();
}

bool SocketUtils::BindIOCPCallback(const SOCKET sock, GUID guid, LPVOID* fn)
{
	DWORD bytes = 0;
	return SOCKET_ERROR != ::WSAIoctl(sock, SIO_GET_EXTENSION_FUNCTION_POINTER, &guid, sizeof(guid), fn, sizeof(*fn), OUT & bytes, nullptr, nullptr);
	return false;
}

SOCKET SocketUtils::CreateSocket()
{
	return ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);
}

bool SocketUtils::SetLinger(const SOCKET sock, const uint16 onoff, const uint16 linger)
{
	LINGER l;
	l.l_onoff = onoff;
	l.l_linger = linger;
	return SetSockOpt(sock, SOL_SOCKET, SO_LINGER, l);
}

bool SocketUtils::SetReuseAddress(const SOCKET sock, const bool flag)
{
	return SetSockOpt(sock, SOL_SOCKET, SO_REUSEADDR, flag);
}

bool SocketUtils::SetRecvBufferSize(const SOCKET sock, const int32 size)
{
	return SetSockOpt(sock, SOL_SOCKET, SO_RCVBUF, size);
}

bool SocketUtils::SetSendBufferSize(const SOCKET sock, const int32 size)
{
	return SetSockOpt(sock, SOL_SOCKET, SO_SNDBUF, size);
}

bool SocketUtils::SetTcpNoDelay(const SOCKET sock, const bool flag)
{
	return SetSockOpt(sock, SOL_SOCKET, TCP_NODELAY, flag);
}

bool SocketUtils::SetUpdateAcceptSocket(const SOCKET sock, const SOCKET listenSocket)
{
	return SetSockOpt(sock, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, listenSocket);
}

bool SocketUtils::Bind(const SOCKET socket, NetAddr_TCP& netAddr)
{
	return SOCKET_ERROR != bind(socket, reinterpret_cast<const sockaddr*>(&netAddr.GetSockAddr()), sizeof(sockaddr_in));
}

bool SocketUtils::Bind(const SOCKET socket, const uint16 port)
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	return SOCKET_ERROR != bind(socket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
	return false;
}

bool SocketUtils::Listen(const SOCKET sock, const int32 backLog)
{
	return SOCKET_ERROR != listen(sock, backLog);
}

void SocketUtils::CloseSocket(SOCKET& socket)
{
	if (socket != INVALID_SOCKET)
		closesocket(socket);
	socket = INVALID_SOCKET;
}
