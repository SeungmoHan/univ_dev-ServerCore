#pragma once

class Session;

enum class EventType : uint8
{
	Connect,
	Disconnect,
	Accept,

	// PreRecv, // For Zerobytes Recv
	Recv,
	Send,
};

/*---------------
	Iocp Event
---------------*/


class IocpEvent : public OVERLAPPED
{
public:
	IocpEvent(EventType type);

	void Init();

public:
	EventType		eventType;
	IocpObjectRef	owner;
};


/*--------------------
	Connect Event
---------------------*/
class ConnectEvent : public IocpEvent
{
public:
	ConnectEvent() : IocpEvent(EventType::Connect) {};
};
/*--------------------
   Disconnect Event
---------------------*/
class DisconnectEvent : public IocpEvent
{
public:
	DisconnectEvent() : IocpEvent(EventType::Disconnect) {};
};


/*--------------------
	 Accept Event
---------------------*/
class AcceptEvent : public IocpEvent
{
public:
	AcceptEvent() : IocpEvent(EventType::Accept) {};

public:
	SessionRef session = nullptr;
};



/*--------------------
	  Recv Event
---------------------*/
class RecvEvent : public IocpEvent
{
public:
	RecvEvent() : IocpEvent(EventType::Recv) {};
};
/*--------------------
	  Send Event
---------------------*/
class SendEvent : public IocpEvent
{
public:
	SendEvent() : IocpEvent(EventType::Send) {};

	//   [2/20/2023 SeungmoHan] temp
	Vector<SendBufferRef> sendBuffers;
};