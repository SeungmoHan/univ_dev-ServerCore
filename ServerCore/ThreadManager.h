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

	void		Launch(function<void(void)> callback);
	void		Join();

	static void InitTLS();
	static void DestroyTLS();


private:
	Mutex			m_Lock;
	vector<thread>	m_Threads;


};

