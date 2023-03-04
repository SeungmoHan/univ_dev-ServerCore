#include "pch.h"
#include <iostream>

#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"

#include "GameSessionManager.h"


int main()
{
	
	//TODO
	ServerServiceRef service = MakeShared<ServerService>(
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
	char sendData[] = "Hello World!";
	while (true)
	{
		SendBufferRef sendBuffer = g_SendBufferManager->Open(4096);

		BYTE* buffer = sendBuffer->Buffer();
		((PacketHeader*)buffer)->size = sizeof(sendData) + sizeof(PacketHeader);
		((PacketHeader*)buffer)->id = 1;

		memcpy_s(buffer + 4, sizeof(sendData), sendData, sizeof(sendData));
		sendBuffer->Close(sizeof(sendData) + sizeof(PacketHeader));
		GameSessionManager::Instance()->Broadcast(sendBuffer);

		this_thread::sleep_for(250ms);
	}
	g_ThreadManager->Join();
}