#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"
#include "DeadLockProfiler.h"
#include "Memory.h"
#include "SendBuffer.h"
#include "SocketUtils.h"
#include "Logger.h"

ThreadManager*			g_ThreadManager = nullptr;
DeadLockProfiler*		g_DeadlockProfiler = nullptr;
Memory*					g_Memory = nullptr;
SendBufferManager*		g_SendBufferManager = nullptr;


class CoreGlobal
{
public:
	CoreGlobal()
	{
		g_Memory = new Memory();
		g_ThreadManager = new ThreadManager();
		g_SendBufferManager = new SendBufferManager();
		g_DeadlockProfiler = new DeadLockProfiler();
		SocketUtils::Init();
	}
	~CoreGlobal()
	{
		delete g_DeadlockProfiler;
		delete g_ThreadManager;
		delete g_Memory;
		delete g_SendBufferManager;
		SocketUtils::Clear();
	}
}GCoreGlobal;