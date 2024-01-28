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

#include "Channel.h"
#include "ChannelManager.h"
#include "GameRoomManager.h"

enum
{
	WORKER_TICK = 64,
};


void WorkerThread(const ServerServicePtr& service)
{
	GameServer::Instance()->IncreaseRunningThreadCounts();
	while (GameServer::Instance()->IsRunning() == false)
		this_thread::sleep_for(1s);
	while (true)
	{
		if (GameServer::Instance()->IsClosing() == true)
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
	// 게임채널의 목적 -> 각각 분리된 환경이 조성되어야 하는 콘텐츠들을 위함
	// ex) 각 채널마다의 맵이라던가 그런것들...
	// 게임서버의 목적 -> 범채널 콘텐츠를 다루기 위함...
	// ex) 길드, 파티, 채팅과관련된것들...
	// 룸(파티) 업데이트 시작
	GameRoomManager::Instance().Update(deltaTick);


	// 그외 콘텐츠들 있으면 여기 밑에서 업데이트 되도록 
	//GuildManager::Instance()->UpdatE(deltaTick); // 일단 얘까지는 포폴에 넣고싶다...
	return true;
}


void GameServer::InitChannel()
{
	// 굳이 서버에서 채널을 관리할 필요가 있을까..?
	// 싱글톤화 되어서 어디서든 접근 가능한데...
	// 이부분에 대한 설계를 다시 고민해봐야겠다...
	// 디폴트 채널 0채널 => 로그인 직후 아직 채널선택이 되지 않은 유저들을 보낼 채널
	for (int i = 0; i < m_ServerOption.m_ChannelCounts + 1; i++)
		CreateChannel();
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

	m_UpdateControl = MakeShared<UpdateTickControl>(m_ServerOption.m_ServerFPS);

	InitChannel();


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
		m_UpdateControl->Init();
		while (IsClosing() == false)
		{
			if (Update(m_UpdateControl->GetDeltaTick()) == false)
			{
				cout << "Update Error" << endl;
				m_ServerStartFlag = false;
				m_ServerClosingFlag = true;
				break;
			}
			m_UpdateControl->Update();
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


uint32 GameServer::RebootChannel(const uint32 channelKey)
{
	if(ChannelManager::Instance().DetatchChannel(channelKey))
		return 0;

	return ChannelManager::Instance().AttatchChannel();
}

void GameServer::CloseChennel(const uint32 channelKey)
{
	ChannelManager::Instance().DetatchChannel(channelKey);
}

uint32 GameServer::CreateChannel()
{
	return ChannelManager::Instance().AttatchChannel();
}

bool GameServer::InitConfigParser()
{
	ConfigParser config;
	ASSERT_CRASH(config.LoadConfig(L"ServerOptions/ServerOption.ini"));
	// ServerOption Read
	{
		ASSERT_CRASH(config.SetCurrentSection(L"ServerOptions"));
		wstring modeStr; // 스크립트의 모드는 스트링이고 타입은 enum값이라서,,,
		ASSERT_CRASH(config.Get(L"ScriptPath",				m_ServerOption.m_DataScriptPath));
		ASSERT_CRASH(config.Get(L"LogPath",					m_ServerOption.m_LogPath));
		ASSERT_CRASH(config.Get(L"IP",						m_ServerOption.m_IP));
		ASSERT_CRASH(config.Get(L"ListenPort",				m_ServerOption.m_Port));
		ASSERT_CRASH(config.Get(L"MaxSessions",				m_ServerOption.m_MaxSessionCounts));
		ASSERT_CRASH(config.Get(L"ServerFrame",				m_ServerOption.m_ServerFPS));
		ASSERT_CRASH(config.Get(L"WorkerThreadCnt",			m_ServerOption.m_WorkerThreadCounts));
		ASSERT_CRASH(config.Get(L"ChannelCounts",			m_ServerOption.m_ChannelCounts));
		ASSERT_CRASH(config.Get(L"MaxCharacterPerPlayer",	m_ServerOption.m_MaxCharacterPerPlayer));
		ASSERT_CRASH(config.Get(L"MaxSectorSize",			m_ServerOption.m_MaxSectorSize));
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
