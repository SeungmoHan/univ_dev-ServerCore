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

using SessionAllocator = function<SessionPtr(void)>;

class Service : public enable_shared_from_this<Service>
{
public:
	Service(ServiceType type, NetAddr_TCP address, IocpCorePtr core, SessionAllocator factory, int32 maxSessionCount = 1);
	virtual ~Service();

	virtual bool	Start() abstract;
	bool			CanStart() const { return m_SessionAllocator != nullptr; }
	virtual void	CloseService();
	void			SetSessionAllocator(const SessionAllocator& factory) { m_SessionAllocator = factory; }


	void			Broadcast(const SendBufferPtr sendBuffer);
	SessionPtr		CreateSession();
	void			AddSession(SessionPtr session);
	void			ReleaseSession(SessionPtr session);
	int32			GetCurrentSessionCount() const { return m_SessionCounts; }
	int32			GetMaxSessionCount() const { return m_MaxSessionCounts; }

public:
	ServiceType		GetServiceType() const { return m_Type; }
	NetAddr_TCP&		GetNetAddress() { return m_Addr; }
	IocpCorePtr&	GetIocpCore() { return m_IocpCore; }
public:


protected:
	USE_LOCK;

	ServiceType			m_Type;
	NetAddr_TCP			m_Addr;
	IocpCorePtr			m_IocpCore;

	Set<SessionPtr>		m_Sessions;
	int32				m_SessionCounts = 0;
	int32				m_MaxSessionCounts = 0;
	SessionAllocator	m_SessionAllocator;
};



/*------------------
	ClientService
------------------*/
class ClientService : public Service 
{
public:
	ClientService(NetAddr_TCP targetAddr, IocpCorePtr core, SessionAllocator factory, int32 maxSessionCount = 1);

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
	ServerService(NetAddr_TCP targetAddr, IocpCorePtr core, SessionAllocator factory, int32 maxSessionCount = 1);
	virtual ~ServerService();

	virtual bool Start() override;
	virtual void CloseService() override;

private:
	ListenerPtr m_Listener = nullptr;
};
