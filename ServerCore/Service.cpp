#include "pch.h"
#include "Service.h"
#include "Session.h"
#include "Listener.h"

Service::Service(const ServiceType type, const NetAddress address, const IocpCoreRef core, const SessionFactory factory, const int32 maxSessionCount)
	: m_Type(type), m_Addr(address) , m_IocpCore(core), m_SessionFactory(factory), m_MaxSessionCounts(maxSessionCount)
{ 

}

Service::~Service() = default;

void Service::CloseService()
{
	//TODO
}

void Service::Broadcast(const SendBufferRef sendBuffer)
{
	WRITE_LOCK;
	for(const auto& session : m_Sessions)
	{
		session->Send(sendBuffer);
	}
}

SessionRef Service::CreateSession()
{
	SessionRef session = m_SessionFactory();
	session->SetService(shared_from_this());
	if (m_IocpCore->Register(session) == false)
		return nullptr;
	return session;
}

void Service::AddSession(SessionRef session)
{
	WRITE_LOCK;
	m_SessionCounts++;
	m_Sessions.emplace(session);
}

void Service::ReleaseSession(const SessionRef session)
{
	WRITE_LOCK;
	ASSERT_CRASH(m_Sessions.erase(session) != 0);
	m_SessionCounts--;
}



/*------------------
	ClientService
------------------*/
ClientService::ClientService(const NetAddress targetAddr, const IocpCoreRef core, const SessionFactory factory, const int32 maxSessionCount)
	:Service(ServiceType::Client, targetAddr, core , factory, maxSessionCount)
{

}

ClientService::~ClientService() = default;

bool ClientService::Start()
{
	//TODO
	if (CanStart() == false)
		return false;

	const int32 sessionCount = GetMaxSessionCount();
	for (int32 i = 0; i < sessionCount; i++)
	{
		if (const SessionRef session = CreateSession(); session->Connect() == false)
			return false;
	}
	return true;
}

void ClientService::CloseService()
{
	Service::CloseService();
}




/*------------------
	ServerService
------------------*/
ServerService::ServerService(const NetAddress addr, const IocpCoreRef core, const SessionFactory factory, const int32 maxSessionCount)
	:Service(ServiceType::Server, addr, core, factory, maxSessionCount)
{
}

ServerService::~ServerService() = default;

bool ServerService::Start()
{
	//TODO
	if (CanStart() == false)
		return false;

	m_Listener = MakeShared<Listener>();
	if (m_Listener == nullptr)
		return false;

	if (const ServerServiceRef service = static_pointer_cast<ServerService>(shared_from_this()); m_Listener->StartAccept(service) == false)
		return false;

	return true;
}

void ServerService::CloseService()
{
	Service::CloseService();
}
