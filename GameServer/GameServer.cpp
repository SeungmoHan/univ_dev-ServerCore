#include "pch.h"
#include <iostream>

#include "ThreadManager.h"
#include "Service.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ServerPacketHandler.h"
#include "Protocol.pb.h"


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
		Protocol::SC_TEST pkt;
		pkt.set_id(1000);
		pkt.set_hp(100);
		pkt.set_attack(10);

		
		{
			Protocol::BuffData* data = pkt.add_buff();
			data->set_buffid(100);
			data->set_remaintime(1.2f);
			data->add_victims(4000);
		}
		{
			Protocol::BuffData* data = pkt.add_buff();
			data->set_buffid(200);
			data->set_remaintime(2.4f);
			data->add_victims(3000);
		}
		{
			Protocol::BuffData* data = pkt.add_buff();
			data->set_buffid(300);
			data->set_remaintime(3.6f);
			data->add_victims(12000);
		}

		const SendBufferRef sendBuffer = ServerPacketHandler::MakeSendBuffer(pkt);
		GameSessionManager::Instance()->Broadcast(sendBuffer);

		this_thread::sleep_for(1000ms);
	}
	g_ThreadManager->Join();
}
