#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "ServerSession.h"
#include "ServerPacketHandler.h"

int main()
{
	ServerPacketHandler::Init();
	this_thread::sleep_for(2000ms);
	const ClientServicePtr service = MakeShared<ClientService>(
		NetAddr_TCP(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>,// Session Factory TODO : SessionManager
		1);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; i++)
	{
		g_ThreadManager->Launch([=]()
			{
				this_thread::sleep_for(1000ms);
		while (true)
		{
			service->GetIocpCore()->Dispatch();
		}
			});
	}
	g_ThreadManager->Join();
}