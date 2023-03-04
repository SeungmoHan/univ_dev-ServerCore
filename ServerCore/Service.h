#pragma once
#include "NetworkAddress.h"
#include "IocpCore.h"
#include "Listener.h"
#include <functional>


enum class ServiceType : uint8
{
	Server,
	Client,
};


/*--------------
	Service
--------------*/

using SessionFactory = function<SessionRef(void)>;

class Service : public enable_shared_from_this<Service>
{
public:
	Service(ServiceType type, NetAddress address, IocpCoreRef core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~Service();

	virtual bool	Start() abstract;
	bool			CanStart() { return m_SessionFactory != nullptr; }
	virtual void	CloseService();
	void			SetSessionFactory(SessionFactory factory) { m_SessionFactory = factory; }

	SessionRef		CreateSession();
	void			AddSession(SessionRef session);
	void			ReleaseSession(SessionRef session);
	int32			GetCurrentSessionCount() { return m_SessionCounts; }
	int32			GetMaxSessionCount() { return m_MaxSessionCounts; }

public:
	ServiceType		GetServiceType() { return m_Type; }
	NetAddress&		GetNetAddress() { return m_Addr; }
	IocpCoreRef&	GetIocpCore() { return m_IocpCore; }
public:


protected:
	USE_LOCK;

	ServiceType			m_Type;
	NetAddress			m_Addr = {};
	IocpCoreRef			m_IocpCore;

	Set<SessionRef>		m_Sessions;
	int32				m_SessionCounts = 0;
	int32				m_MaxSessionCounts = 0;
	SessionFactory		m_SessionFactory;
};



/*------------------
	ClientService
------------------*/
class ClientService : public Service 
{
public:
	ClientService(NetAddress targetAddr, IocpCoreRef core, SessionFactory factory, int32 maxSessionCount = 1);

	virtual ~ClientService();
	virtual bool Start() override;
	virtual void CloseService();

};


/*------------------
	ServerService
------------------*/
class ServerService : public Service
{
public:
	ServerService(NetAddress targetAddr, IocpCoreRef core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~ServerService();

	virtual bool Start() override;
	virtual void CloseService();

private:
	ListenerRef m_Listener = nullptr;
};
