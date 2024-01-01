#pragma once


struct JobData
{
	JobData(weak_ptr<JobSerializer> owner, JobPtr job) : owner(owner), job(job){}

	weak_ptr<JobSerializer> owner;
	JobPtr					job;
};

struct TimerItem
{
	bool operator<(const TimerItem& other) const
	{
		return executeTick > other.executeTick;
	}

	uint64 executeTick = 0;
	JobData* jobData = nullptr;
};


/*-----------------
	JobTimer
-----------------*/
class JobTimer
{
public:
	void Reserve(uint64 tickAfter, weak_ptr<JobSerializer> owner, JobPtr job);
	void Execute(uint64 now);
	void Clear();



private:
	PriorityQueue<TimerItem>	m_Items;
	Atomic<bool>				m_Distributing = false;
	USE_LOCK;
};
