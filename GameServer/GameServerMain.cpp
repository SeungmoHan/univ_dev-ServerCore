#include "pch.h"
#include "GameServer.h"
#include "ThreadManager.h"

int main()
{
	// 타이머 인터럽트 주기 1ms로 변경
	timeBeginPeriod(1);

	GameServer::Instance()->Init();
	GameServer::Instance()->Run();

}
