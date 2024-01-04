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
#include "UpdateTickControl.h"

#include <functional>

#include "GameRoomManager.h"

enum
{
	WORKER_TICK = 64,
};


void WorkerThread(const ServerServicePtr& service)
{
	GameServer::Instance().IncreaseRunningThreadCounts();
	while (GameServer::Instance().IsRunning() == false)
		this_thread::sleep_for(1s);
	while (true)
	{
		if (GameServer::Instance().IsClosing() == true)
			break;

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
	g_Logger->PushLog(L"[%s @%d] Update Frame %d", 
		__FUNCTIONW__, __LINE__, m_UpdateControl->GetServerFrame());
	// 플레이들 업데이트 먼저하고
	GameSessionManager::Instance()->Update(deltaTick);

	// 룸 업데이트 시작
	GameRoomManager::Instance().Update(deltaTick);

	// 그외 콘텐츠들 있으면 여기 밑에서 업데이트 되도록 
	return true;
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

	m_UpdateControl = MakeShared<UpdateTickControl>(*this, m_ServerOption.m_ServerFPS);


	return m_ServerStartFlag = true;
}

void GameServer::Run()
{
	if(IsRunning() == false)
	{
		cout << "server not initiated" << endl;
		return;
	}

	while (m_WorkerRunningCounts != m_ServerOption.m_WorkerThreadCounts)
		this_thread::sleep_for(1s);

	g_ThreadManager->Launch([this]()
	{
		// Update Thread Create
		uint64 lastTick = GetTickCount64();
		while(IsRunning() == false)
			this_thread::sleep_for(1s);
		while (IsClosing() == false)
		{
			static int i = 0;
			if (m_UpdateControl->Update() == true)
			{
				if (Update(m_UpdateControl->GetDeltaTick()) == false)
				{
					cout << "Update Error" << endl;
					m_ServerStartFlag = false;
					m_ServerClosingFlag = true;
					break;
				}
			}
			m_UpdateControl->DelayFrame();
		}
	});

	// Main Thread는 종료 조건을 위한 쓰레드로 남겨두도록 하자...
	// 키에따라 할일이 달라짐
	// Command
	// -> QuitServer	CloseServer
	// -> Shutdown		ShutDown
	//while(true)
	//{
	//	// 키입력을 여기서 받자...
	//	if(m_ServerInputControl.Update() == false)
	//		break;
	//}
	g_ThreadManager->Join();
	cout << "server running flag == false : server off" << endl;
}

void GameServer::Shutdown()
{
	m_ServerClosingFlag = true;
	this_thread::sleep_for(3s);
	m_Service->CloseService();
	GameSessionManager::Instance()->RemoveAll();
}

bool GameServer::InitConfigParser()
{
	ConfigParser config;
	ASSERT_CRASH(config.LoadConfig(L"ServerOptions/ServerOption.ini"));
	// ServerOption Read
	{
		ASSERT_CRASH(config.SetCurrentSection(L"ServerOptions"));
		wstring modeStr; // 스크립트의 모드는 스트링이고 타입은 enum값이라서,,,
		ASSERT_CRASH(config.Get(L"ScriptPath",		m_ServerOption.m_DataScriptPath));
		ASSERT_CRASH(config.Get(L"LogPath",			m_ServerOption.m_LogPath));
		ASSERT_CRASH(config.Get(L"IP",				m_ServerOption.m_IP));
		ASSERT_CRASH(config.Get(L"ListenPort",		m_ServerOption.m_Port));
		ASSERT_CRASH(config.Get(L"MaxSessions",		m_ServerOption.m_MaxSessionCounts));
		ASSERT_CRASH(config.Get(L"ServerFrame",		m_ServerOption.m_ServerFPS));
		ASSERT_CRASH(config.Get(L"WorkerThreadCnt", m_ServerOption.m_WorkerThreadCounts));
		ASSERT_CRASH(config.Get(L"ServerMode",		modeStr));
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
	m_Service = MakeShared<ServerService>(
		NetAddr_TCP(m_ServerOption.m_IP, m_ServerOption.m_Port),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>,// Session Factory TODO : SessionManager
		m_ServerOption.m_MaxSessionCounts);

	if (m_Service->CanStart() == false)
		return false;
	return m_Service->Start();
}

void GameServer::InitWorkerThread()
{
	for (uint32 i = 0; i < m_ServerOption.m_WorkerThreadCounts; i++)
	{
		g_ThreadManager->Launch([this]()
			{
				this_thread::sleep_for(1s);
				WorkerThread(m_Service);
			}
		);
	}
}
