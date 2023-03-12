#include "pch.h"
#include <iostream>

#include "ThreadManager.h"
#include "Service.h"
#include "GameSession.h"
#include "GameSessionManager.h"
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
		const uint64 id = (rand() % 50) + 51;
		const uint32 hp = (rand() % 50) + 150 + 1;
		const uint16 attack = (rand() % 50) + 250 + 1;
		PKT_SC_TEST_WRITE pktWriter(id, hp, attack);

		const uint32 buffSize = (rand() % 10) + 1;
		PKT_SC_TEST_WRITE::BuffList buffList = pktWriter.ReserveBuffList(buffSize);

		for(uint32 i = 0; i < buffSize ; i++)
		{
			const uint32 buffId = rand() % 10000 + 1;
			const auto up = static_cast<float>((rand() % 5) + 10);
			const auto down = static_cast<float>((rand() % 5) + 1);
			const auto remainTime = up / down;
			buffList[i] = { buffId,remainTime };
		}
		for (uint32 i = 0; i < buffSize; i++)
		{
			const uint32 buffVictimCount = (rand() % 3) + 1;
			PKT_SC_TEST_WRITE::BuffVictimList victim = pktWriter.ReserveBuffVictimList(&buffList[i], buffVictimCount);
			for (uint32 j = 0; j < buffVictimCount; j++)
			{
				victim[j] = (1000 * (j + 1)) + i;
			}
		}

		const SendBufferRef sendBuffer = pktWriter.CloseAndReturn();
		GameSessionManager::Instance()->Broadcast(sendBuffer);

		this_thread::sleep_for(1000ms);
	}
	g_ThreadManager->Join();
}
