#pragma once

#include <thread>
#include <functional>


/*----------------------
	  Thread Manager
----------------------*/

class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	void		Launch(const function<void(void)>& callback);
	void		Join();

	static void InitTLS();
	static void DestroyTLS();

	static void DoGlobalQueueWork();
	static void ExecuteReservedJobs();


private:
	Mutex			m_Lock;
	vector<thread>	m_Threads;


};

