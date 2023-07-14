#include "pch.h"
#include <iostream>

#include "ThreadManager.h"
#include "Service.h"
#include "GameSession.h"
#include "ClientPacketHandler.h"
#include "Protocol.pb.h"
#include "Job.h"
#include "Room.h"


void HealByValue(const uint64 target, const int32 value)
{
	cout << target << "에게 " << value << " 만큼 회복" << endl;
}

class Knight
{
public:
	void HealMe(int32 value)
	{
		cout << "HealMe! : " << value << endl;
	}
};

int main()
{
	// TEST Job
	//{
	//	FuncJob job(HealByValue, 100, 10);
	//	job.Execute();
	//}
	//{
	//	Knight n1;
	//	MemberJob job(&n1, &Knight::HealMe, 100);
	//	job.Execute();
	//}
	// Job

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
		g_Room.FlushJob();
		this_thread::sleep_for(10ms);
	}

	g_ThreadManager->Join();
}
