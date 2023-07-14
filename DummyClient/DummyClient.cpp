#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "ServerPacketHandler.h"



char sendData[] = "Hello World!";
class ServerSession : public PacketSession
{
public:
	virtual void	OnConnect() override
	{
		Protocol::CS_LOGIN loginPacket;
		const auto buffer = ServerPacketHandler::MakeSendBuffer(loginPacket);
		Send(buffer);
	}

	virtual void	OnRecvPacket(BYTE* buffer, const int32 len) override
	{
		auto session = GetPacketSessionRef();
		auto header = reinterpret_cast<PacketHeader*>(buffer);

		ServerPacketHandler::HandlePacket(session, buffer, len);
	}
	virtual void	OnSend(int32 len) override
	{
		//cout << "OnSend Len = " << len <<  endl;
	};
	virtual void	OnDisconnected() override {};
};

int main()
{
	ServerPacketHandler::Init();
	this_thread::sleep_for(2000ms);
	const ClientServiceRef service = MakeShared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<ServerSession>,// Session Factory TODO : SessionManager
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

	Protocol::CS_NORMAL_CHAT chatPkt;
	chatPkt.set_msg(u8"Hello World!");
	const auto sendBuffer = ServerPacketHandler::MakeSendBuffer(chatPkt);

	while(true)
	{
		service->Broadcast(sendBuffer);
		this_thread::sleep_for(1s);
	}
	g_ThreadManager->Join();
}