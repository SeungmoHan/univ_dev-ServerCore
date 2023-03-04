#include "pch.h"
#include <iostream>

#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"

#include "GameSessionManager.h"
#include "BufferWriter.h"

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
	constexpr char sendData[] = "Hello World!";
	while (true)
	{
		const SendBufferRef sendBuffer = g_SendBufferManager->Open(4096);

		BufferWriter writer(sendBuffer->Buffer(), 4096);

		auto* header = writer.Reserve<PacketHeader>();

		//id(uint64), 체력 uint32, 공격력 uint16
		writer << static_cast<uint64>(1001) << static_cast<uint32>(100) << static_cast<uint16>(10);
		writer.Write(sendData, sizeof(sendData));

		header->size = writer.WriteSize();
		header->id = 1;


		sendBuffer->Close(writer.WriteSize());
		GameSessionManager::Instance()->Broadcast(sendBuffer);

		this_thread::sleep_for(250ms);
	}
	g_ThreadManager->Join();
}