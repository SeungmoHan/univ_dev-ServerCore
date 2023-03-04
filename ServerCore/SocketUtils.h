#pragma once



class NetAddress;
/*--------------------
	SOCKET Util
--------------------*/
class SocketUtils
{
public:
	static LPFN_CONNECTEX		ConnectEx;
	static LPFN_DISCONNECTEX	DisconnectEx;
	static LPFN_ACCEPTEX		AcceptEx;

public:
	static void Init();
	static void Clear();

	static bool BindWindowsFunction(SOCKET sock, GUID guid, LPVOID* fn);
	static SOCKET CreateSocket();

	static bool SetLinger(SOCKET sock, uint16 onoff, uint16 linger);
	static bool SetReuseAddress(SOCKET sock, bool flag);
	static bool SetRecvBufferSize(SOCKET sock, int32 size);
	static bool SetSendBufferSize(SOCKET sock, int32 size);
	static bool SetTcpNoDelay(SOCKET sock, bool flag);
	static bool SetUpdateAcceptSocket(SOCKET sock, SOCKET listenSocket);


	static bool Bind(SOCKET socket, NetAddress& netAddr);
	static bool BindAnyAddress(SOCKET socket, uint16 port);
	static bool Listen(SOCKET sock, int32 backLog = SOMAXCONN);
	static void Close(SOCKET& socket);
};

template <typename T>
static inline bool SetSockOpt(const SOCKET socket, const int32 level, const int32 optName, T optVal)
{
	return SOCKET_ERROR != setsockopt(socket, level, optName, reinterpret_cast<char*>(&optVal), sizeof(T));
}