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
		vector<BuffData> buffs;

		const uint64 id = (rand() % 50) + 51;
		const uint32 hp = (rand() % 50) + 150 + 1;
		const uint16 attack = (rand() % 50) + 250 + 1;

		const uint32 buffSize = (rand() % 10) + 1;
		buffs.resize(buffSize);
		for(uint32 i = 0; i<buffSize ; i++)
		{
			const uint32 buffId = rand() % 10000 + 1;
			const auto up = static_cast<float>((rand() % 5) + 10);
			const auto down = static_cast<float>((rand() % 5) + 1);
			const auto remainTime = up / down;
			buffs[i] = { buffId,remainTime };
		}

		const SendBufferRef sendBuffer = ServerPacketHandler::Make_SC_TEST(id, hp, attack, buffs, L"안녕하세요");

		GameSessionManager::Instance()->Broadcast(sendBuffer);

		this_thread::sleep_for(1000ms);
	}
	g_ThreadManager->Join();
}
