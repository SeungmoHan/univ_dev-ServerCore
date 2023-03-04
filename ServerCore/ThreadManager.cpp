#include "pch.h"
#include "ThreadManager.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"

ThreadManager::ThreadManager()
{
	InitTLS();
}

ThreadManager::~ThreadManager()
{
	Join();
}

void ThreadManager::Launch(const function<void(void)>& callback)
{
	LockGuard guard(m_Lock);

	m_Threads.emplace_back([=]()
		{
			InitTLS();
			callback();
			DestroyTLS();
		});
}

void ThreadManager::Join()
{
	for (std::thread& t : m_Threads)
	{
		t.join();
	}
	m_Threads.clear();
}

void ThreadManager::InitTLS()
{
	static Atomic<uint32> SThreadId = 1;
	LThreadId = SThreadId.fetch_add(1);
}

void ThreadManager::DestroyTLS()
{

}
