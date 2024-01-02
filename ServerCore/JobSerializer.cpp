#include "pch.h"
#include "JobSerializer.h"
#include "GlobalQueue.h"

void JobSerializer::Push(JobPtr job, bool pushOnly)
{
	const int32 prevCounts = m_JobCounts.fetch_add(1);
	m_Jobs.Push(job);

	//첫번째 작업자만 실행까지 담당
	if(prevCounts == 0)
	{
		if(LCurrentJobQueue == nullptr && pushOnly == false)
		{
			Execute();
		}
		else
		{
			// 여유 있는 다른 쓰레드가 실행하도록 Global Queue에 넘긴다
			g_GlobalQueue->Push(shared_from_this());
		}
	}
}

void JobSerializer::Execute()
{
	LCurrentJobQueue = this;

	while(true)
	{
		Vector<JobPtr> jobs;
		m_Jobs.PopAll(jobs);

		const auto jobCounts = static_cast<int32>(jobs.size());
		for (const auto& job : jobs)
			job->Execute();

		if (m_JobCounts.fetch_sub(jobCounts) == jobCounts)
		{
			LCurrentJobQueue = nullptr;
			break;
		}

		const uint64 now = ::GetTickCount64();
		if(now >= LEndTickCount)
		{
			LCurrentJobQueue = nullptr;
			// 여유 있는 다른 쓰레드가 실행하도록 Global Queue에 넘긴다
			g_GlobalQueue->Push(shared_from_this());
		}

		// 위에서 break가 안되었으면 다른쓰레드가 fetch_add를 해놓고 m_Jobs.Push를 못한상태임
		// 그Job을 Push할 수 있게 잠깐 cpu점유를 놓아준다.
		this_thread::yield();
	}
}
