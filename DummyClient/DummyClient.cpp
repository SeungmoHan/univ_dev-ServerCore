#include "pch.h"
#include <iostream>

#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"


char sendData[] = "Hello World!";
class ServerSession : public Session
{
public:
	virtual void	OnConnect() 
	{
		cout << "Connect To Server" << endl;
		SendBufferRef sendBuffer = g_SendBufferManager->Open(4096);
		memcpy_s(sendBuffer->Buffer(), sizeof(sendData), sendData, sizeof(sendData));
		sendBuffer->Close(sizeof(sendData));

		Send(sendBuffer);
	};
	virtual int32	OnRecv(BYTE* buffer, int32 len) override
	{
		SendBufferRef sendBuffer = g_SendBufferManager->Open(4096);
		memcpy_s(sendBuffer->Buffer(), sizeof(sendData), sendData, sizeof(sendData));
		sendBuffer->Close(sizeof(sendData));

		Send(sendBuffer);

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
		5);

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