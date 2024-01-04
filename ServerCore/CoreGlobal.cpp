#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"
#include "DeadLockProfiler.h"
#include "GlobalQueue.h"
#include "SendBuffer.h"
#include "SocketUtils.h"
#include "Logger.h"
#include "JobTimer.h"
#include "DBConnectionPool.h"

ThreadManager*			g_ThreadManager = nullptr;
DeadLockProfiler*		g_DeadlockProfiler = nullptr;
SendBufferManager*		g_SendBufferManager = nullptr;
JobTimer*				g_JobTimer = nullptr;
GlobalQueue*			g_GlobalQueue = nullptr;
DBConnectionPool*		g_DBConnectionPool= nullptr;
Logger*					g_Logger = nullptr;

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
		if (!g_GlobalQueue)
			g_GlobalQueue = new GlobalQueue();
		if (!g_JobTimer)
			g_JobTimer = new JobTimer();
		if (!g_DBConnectionPool)
			g_DBConnectionPool = new DBConnectionPool();
		if (!g_Logger)
			g_Logger = new Logger();
		SocketUtils::Init();
	}
	~CoreGlobal()
	{
		delete g_DeadlockProfiler;
		delete g_ThreadManager;
		delete g_SendBufferManager;
		delete g_JobTimer;
		delete g_GlobalQueue;
		delete g_DBConnectionPool;
		delete g_Logger;
		SocketUtils::Clear();
	}
}GCoreGlobal;