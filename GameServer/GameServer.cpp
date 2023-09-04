#include "pch.h"

#include "ThreadManager.h"
#include "Service.h"
#include "GameSession.h"
#include "ClientPacketHandler.h"
#include "Protocol.pb.h"

#include <functional>

#include "Room.h"


enum
{
	WORKER_TICK = 64,
};

void DoWorkerJob(const ServerServiceRef& service)
{
	while(true)
	{
		LEndTickCount = ::GetTickCount64() + WORKER_TICK;
		service->GetIocpCore()->Dispatch(10);

		// 예약되어있는 일감들 글로벌 큐에 푸시
		ThreadManager::ExecuteReservedJobs();

		// 글로벌 큐 푸쉬
		ThreadManager::DoGlobalQueueWork();
	}
}

int main()
{
	g_Room->DoTimer(1000, [] {cout << "Hello 1" << endl; });
	g_Room->DoTimer(2000, [] {cout << "Hello 2" << endl; });
	g_Room->DoTimer(3000, [] {cout << "Hello 3" << endl; });

	// 타이머 인터럽트 주기 1ms로 변경
	timeBeginPeriod(1);

	//ConfigParser parser;
	//parser.LoadConfig(L"../HelloWorld/ServerOption.txt");

	ClientPacketHandler::Init();
	//TODO
	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>,// Session Factory TODO : SessionManager
		100);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 8; i++)
	{
		g_ThreadManager->Launch([&service]()
			{
				this_thread::sleep_for(1000ms);
				while (true)
				{
					DoWorkerJob(service);
				}
			});
	}

	//Main Thread
	DoWorkerJob(service);

	g_ThreadManager->Join();
}
