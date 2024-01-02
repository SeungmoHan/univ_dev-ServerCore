#pragma once
#include "IocpCore.h"
#include "NetworkAddress.h"


class AcceptEvent;
class ServerService;

/*----------------
	Listener
----------------*/
class Listener : public IocpObject
{
public:
	Listener() = default;
	virtual ~Listener();

public:
	bool StartAccept(const ServerServicePtr& service);
	void CloseSocket();


public:
	/*Interface Impl*/
	virtual HANDLE GetHandle() override;
	virtual void Dispatch(class IocpEvent* iocpEvent, int32 numberOfBytes) override;


private:
	void RegisterAccept(AcceptEvent* acceptEvent);
	void ProcessAccept(AcceptEvent* acceptEvent);


protected:
	SOCKET m_Socket = INVALID_SOCKET;
	Vector<AcceptEvent*>m_AcceptEvents;
	ServerServicePtr m_Service;
};

