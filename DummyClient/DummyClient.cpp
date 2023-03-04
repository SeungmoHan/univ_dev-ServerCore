#include "pch.h"
#include <iostream>

#include "BufferReader.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"

char sendData[] = "Hello World!";
class ServerSession : public PacketSession
{
public:
	virtual void	OnConnect() override { }

	virtual int32	OnRecvPacket(BYTE* buffer, const int32 len) override
	{

		BufferReader reader(buffer, len);

		PacketHeader header{};
		reader >> header;

		uint64 id;
		uint32 hp;
		uint16 attack;

		reader >> id >> hp >> attack;

		cout << "ID : " << id << " HP : " << hp << " ATTACK : " << attack << endl;

		char recvBuffer[4096];
		const auto size = static_cast<uint32>(header.size - sizeof(PacketHeader) - 8 - 4 - 2);
		reader.Read(recvBuffer, size);
		cout << recvBuffer << endl;

		return len;
	}
	virtual void	OnSend(int32 len) override
	{
		//cout << "OnSend Len = " << len <<  endl;
	};
	virtual void	OnDisconnected() override {};
};


int main()
{
	this_thread::sleep_for(5000ms);
	const ClientServiceRef service = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>,// Session Factory TODO : SessionManager
		1000);

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