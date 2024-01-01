#include "pch.h"
#include "GameServer.h"
#include "ThreadManager.h"

using GameServerPtr = shared_ptr<GameServer>;

int main()
{
	// 타이머 인터럽트 주기 1ms로 변경
	timeBeginPeriod(1);

	GameServerPtr gameServer = MakeShared<GameServer>();

	gameServer->Init();
	gameServer->Run();

}
