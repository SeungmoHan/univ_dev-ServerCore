#include "pch.h"
#include "JobTimer.h"
#include "JobSerializer.h"

/*-----------------
	JobTimer
-----------------*/

void JobTimer::Reserve(uint64 tickAfter, weak_ptr<JobSerializer> owner, JobPtr job)
{
	const uint64 executeTick = GetTickCount64() + tickAfter;
	JobData* jobData = ObjectPool<JobData>::Pop(owner, job);

	WRITE_LOCK; //여기 아래부턴 thread_safe하지않음
	m_Items.push(TimerItem{ executeTick, jobData });
}

void JobTimer::Execute(uint64 now)
{
	// 한번에 1쓰레드만 작업할수있게 사용중이었으면 리턴
	if (m_Distributing.exchange(true) == true)
		return;

	Vector<TimerItem> tempItems;
	{
		WRITE_LOCK;
		while(m_Items.empty() == false)
		{
			const auto& item = m_Items.top();
			if (now <= item.executeTick)
				break;

			tempItems.push_back(item);
			m_Items.pop();
		}
	}

	// 이구간에서 컨텍스트 스위칭 걸리면 잡 순서 꼬일수있음.
	for(auto& item : tempItems)
	{
		if(JobSerializerPtr owner = item.jobData->owner.lock())
		{
			owner->Push(item.jobData->job, true);
		}
		ObjectPool<JobData>::Push(item.jobData);
	}

	m_Distributing.store(false);
}

void JobTimer::Clear()
{
	WRITE_LOCK;

	while(m_Items.empty() == false)
	{
		const auto& item = m_Items.top();
		ObjectPool<JobData>::Push(item.jobData);
		m_Items.pop();
	}
}
