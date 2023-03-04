#include "pch.h"
#include <iostream>

#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "BufferWriter.h"
#include "ServerPacketHandler.h"

int main()
{
	//TODO
	const ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>,// Session Factory TODO : SessionManager
		100);

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
	while (true)
	{
		vector<BuffData> buffs{ {100,1.5f}, {200,2.3f}, {300,0.7f} };

		const SendBufferRef sendBuffer = ServerPacketHandler::Make_SC_TEST(101, 102, 103, buffs);

		GameSessionManager::Instance()->Broadcast(sendBuffer);

		this_thread::sleep_for(250ms);
	}
	g_ThreadManager->Join();
}
