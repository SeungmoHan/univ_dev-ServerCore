#include "pch.h"
#include <iostream>

#include "ThreadManager.h"
#include "Service.h"
#include "GameSession.h"
#include "ClientPacketHandler.h"
#include "Protocol.pb.h"
#include "Job.h"
#include "Room.h"

#include <functional>

int main()
{
	ClientPacketHandler::Init();
	//TODO
	const ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>,// Session Factory TODO : SessionManager
		100);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 1; i++)
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

	while(true)
	{
		this_thread::sleep_for(1000ms);
	}

	g_ThreadManager->Join();
}
