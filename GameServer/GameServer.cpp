#include "pch.h"
#include "ConfigParser.h"
#include "GameScriptParser.h"

#include "ThreadManager.h"
#include "Service.h"
#include "GameSession.h"
#include "ClientPacketHandler.h"

#include "Protocol.pb.h"
#include "GameServer.h"
#include "GameSessionManager.h"

#include <functional>

enum
{
	WORKER_TICK = 64,
};


void WorkerThread(const ServerServicePtr& service)
{
	while (true)
	{
		LEndTickCount = ::GetTickCount64() + WORKER_TICK;
		service->GetIocpCore()->Dispatch(10);

		// 예약되어있는 일감들 글로벌 큐에 푸시
		ThreadManager::ExecuteReservedJobs();

		// 글로벌 큐 실행
		ThreadManager::DoGlobalQueueWork();
	}
}


bool GameServer::Update(uint64 deltaTick)
{
	// 플레이들 업데이트 먼저하고
	GameSessionManager::Instance()->Update(deltaTick);

	// 룸 업데이트 시작
	//GameRoomManager::Instance()->Update(deltaTick);

	// 그외 콘텐츠들 있으면 여기 밑에서 업데이트 되도록 
	return true;
}

bool GameServer::CheckUpdate(OUT uint64& deltaTick)
{
	static uint64 beginTick = GetTickCount64();
	const uint64 curTick = GetTickCount64();
	// 1다음번 프레임 시간을 구해야한다...
	const uint64 timeSpendOnEachFrame = 1000 / m_ServerOption.m_ServerFPS;


	// 계산된 다음번 틱이 
	if(calculatedNextTick <= curTick)
		return false;

	


	return false;
}

bool GameServer::Init()
{
	if(InitConfigParser() == false)
		return false;
	if (InitScriptParser() == false)
		return false;

	ClientPacketHandler::Init();

	if (InitServerService() == false)
		return false;
	InitWorkerThread();

	return m_ServerRunningFlag = true;
}

void GameServer::Run()
{
	if(m_ServerRunningFlag == false)
	{
		cout << "server not initiated" << endl;
		return;
	}
	uint64 deltaTick = 0;
	while(m_ServerRunningFlag == true && CheckUpdate(deltaTick) == true)
	{
		if (Update(10) == false)
		{
			cout << "Update Error" << endl;
			m_ServerRunningFlag = false;
			break;
		}
	}

	cout << "server running flag == false : server off" << endl;
	g_ThreadManager->Join();
}


bool GameServer::InitConfigParser()
{
	ConfigParser config;
	ASSERT_CRASH(config.LoadConfig(L"ServerOptions/ServerOption.ini"));
	// ServerOption Read
	{
		ASSERT_CRASH(config.SetCurrentSection(L"ServerOptions"));
		wstring modeStr; // 스크립트의 모드는 스트링이고 타입은 enum값이라서,,,
		ASSERT_CRASH(config.Get(L"ScriptPath", m_ServerOption.m_DataScriptPath));
		ASSERT_CRASH(config.Get(L"IP", m_ServerOption.m_IP));
		ASSERT_CRASH(config.Get(L"ListenPort", m_ServerOption.m_Port));
		ASSERT_CRASH(config.Get(L"ListenPort", m_ServerOption.m_MaxSessionCounts));
		ASSERT_CRASH(config.Get(L"ListenPort", m_ServerOption.m_ServerFPS));
		ASSERT_CRASH(config.Get(L"ServerMode", modeStr));
		m_ServerOption.m_Mode = ServerOptionData::StringToMode(modeStr);
	}
	// 필요한 데이터는 섹션 선택해놓고 찾으면됨...
	return true;
}

bool GameServer::InitScriptParser()
{
	return true;
}

bool GameServer::InitServerService()
{
	//TODO Service에 들어가는 정보들 초기화 컨피그에서읽은거로...
	ServerServicePtr service = MakeShared<ServerService>(
		NetAddr_TCP(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>,// Session Factory TODO : SessionManager
		100);

	if (service->CanStart() == false)
		return false;
	m_Service = std::move(service);
	return m_Service->Start();
}

void GameServer::InitWorkerThread()
{
	for (int32 i = 0; i < 4; i++)
	{
		g_ThreadManager->Launch([this]()
			{
				this_thread::sleep_for(1000ms);
				while (true)
				{
					WorkerThread(m_Service);
				}
			}
		);
	}
}
