#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"
#include "DeadLockProfiler.h"
#include "SendBuffer.h"
#include "SocketUtils.h"
#include "Logger.h"

ThreadManager*			g_ThreadManager = nullptr;
DeadLockProfiler*		g_DeadlockProfiler = nullptr;
SendBufferManager*		g_SendBufferManager = nullptr;


class CoreGlobal
{
public:
	CoreGlobal()
	{
		if(!g_ThreadManager)
			g_ThreadManager = new ThreadManager();
		if(!g_SendBufferManager)
			g_SendBufferManager = new SendBufferManager();
		if(!g_DeadlockProfiler)
			g_DeadlockProfiler = new DeadLockProfiler();
		SocketUtils::Init();
	}
	~CoreGlobal()
	{
		delete g_DeadlockProfiler;
		delete g_ThreadManager;
		delete g_SendBufferManager;
		SocketUtils::Clear();
	}
}GCoreGlobal;