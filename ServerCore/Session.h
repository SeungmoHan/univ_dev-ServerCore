#pragma once
#include "IocpCore.h"
#include "IocpEvent.h"
#include "NetworkAddress.h"
#include "RecvBuffer.h"
#include "ConcurrentQueue.h"
class ServerSession;
class GameSession;
class Service;
/*----------------
	Session
----------------*/

using SessionTL = TypeList<Session, PacketSession, GameSession, ServerSession>;

class Session : public IocpObject
{
	friend class IocpCore;
	friend class Listener;
	friend class Service;

	enum 
	{
		BUFFER_SIZE = 0x10000 // 64k
	};
	DECLARE_TL(SessionTL);
public:

						/* 외부 사용(콘텐츠에 제공할 API)*/
	void				Send(SendBufferPtr buffer);
	bool				Connect();
	void				Disconnect(const WCHAR* reason);

	shared_ptr<Service> GetService() const { return m_Service.lock(); }
	void				SetService(const shared_ptr<Service> service) { m_Service = service; }


public:
	Session();
	virtual ~Session();

	void			SetNetAddress(const NetAddr_TCP addr) { m_NetAddr = addr; }
	NetAddr_TCP		GetAddress() const { return m_NetAddr; }
	SOCKET			GetSocket() const { return m_Socket; }
	bool			IsConnected() const { return m_Connected.load(); }
	SessionPtr		GetSessionPtr() { return static_pointer_cast<Session>(shared_from_this()); }


private:
	/* Interface Impl*/
	virtual HANDLE	GetHandle() override;
	virtual void	Dispatch(class IocpEvent* iocpEvent, int32 numberOfBytes) override;

private:
	/*Send...*/
	bool			RegisterConnect();
	bool			RegisterDisconnect();
	void			RegisterRecv();
	void			RegisterSend();

	void			ProcessConnect();
	void			ProcessDisconnect();
	void			ProcessRecv(int32 numOfBytes);
	void			ProcessSend(int32 numOfBytes);

	void			ErrorHandler(int32 errCode);


protected:

	virtual void	OnConnect() {};
	virtual int32	OnRecv(BYTE* buffer, const int32 len) { return len; }
	virtual void	OnSend(int32 len) {};
	virtual void	OnDisconnected() {};



public:


private:
	weak_ptr<Service>	m_Service;
	SOCKET				m_Socket = INVALID_SOCKET;
	NetAddr_TCP			m_NetAddr;
	Atomic<bool>		m_Connected = false;

private:
	USE_LOCK;
	RecvBuffer			m_RecvBuffer;
	Queue<SendBufferPtr> m_SendQueue;
	Atomic<bool>		m_SendRegistered;
private:
	ConnectEvent m_ConnectEvent;
	DisconnectEvent m_DisconnectEvent;
	RecvEvent m_RecvEvent;
	SendEvent m_SendEvent;
};


/*-----------------------
	Packet	Session
-----------------------*/
struct PacketHeader
{
	uint16 size;
	uint16 id; // protocol (ex 1 로그인 ,2 이동요청등...)
};

class PacketSession : public Session
{
	DECLARE_TL(SessionTL);
public:
	PacketSession();
	virtual ~PacketSession();
	
	PacketSessionPtr GetPacketSessionPtr() { return static_pointer_cast<PacketSession>(shared_from_this()); }
protected:
	virtual int32 OnRecv(BYTE* buffer, int32 len) sealed;
	virtual void OnRecvPacket(BYTE* buffer, int32 len) abstract;
};