#include "pch.h"
#include <iostream>

#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"

class GameSession1 : public Session
{
public:
	~GameSession1() { cout << "~GameSession1" << endl; }
	virtual void	OnConnect() {};
	virtual int32	OnRecv(BYTE* buffer, int32 len) override
	{
		cout << "OnRecv Len =" << len << "  : " << (char*)buffer <<  endl;
		SendBufferRef sendBuffer = g_SendBufferManager->Open(4096);
		memcpy_s(sendBuffer->Buffer(), len, buffer, len);
		sendBuffer->Close(len);
		Send(sendBuffer);
		return len; 
	}
	virtual void	OnSend(int32 len) override 
	{
		cout << "OnSend Len =" << len << endl;
	};
	virtual void	OnDisconnected() {};
};

int main()
{
	
	//TODO
	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>,// Session Factory TODO : SessionManager
		100
		);

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