#include "pch.h"
#include <iostream>

#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"


char sendData[] = "Hello World!";
class ServerSession : public PacketSession
{
public:
	virtual void	OnConnect() 
	{
		
	};
	virtual int32	OnRecvPacket(BYTE* buffer, int32 len) override
	{
		PacketHeader header = *(PacketHeader*)buffer;
		cout << "Packet ID : " << header.id << " Size : " << header.size << endl;

		char recvBuffer[4096];
		memcpy_s(recvBuffer, header.size - sizeof(PacketHeader), buffer + 4, header.size - sizeof(PacketHeader));

		cout << recvBuffer << endl;

		return len;
	}
	virtual void	OnSend(int32 len) override
	{
		//cout << "OnSend Len = " << len <<  endl;
	};
	virtual void	OnDisconnected() {};
};


int main()
{
	this_thread::sleep_for(5000ms);
	ClientServiceRef service = MakeShared<ClientService>(
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