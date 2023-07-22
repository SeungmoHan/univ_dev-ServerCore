#include "pch.h"
#include "JobSerializer.h"


void JobSerializer::Push(JobRef&& job)
{
	const int32 prevCounts = m_JobCounts.fetch_add(1);
	m_Jobs.Push(job);

	//첫번째 작업자만 실행까지 담당
	if(prevCounts == 0)
	{
		Execute();
	}
}

void JobSerializer::Execute()
{
	while(true)
	{
		Vector<JobRef> jobs;
		m_Jobs.PopAll(jobs);

		const auto jobCounts = static_cast<int32>(jobs.size());
		for (const auto& job : jobs)
			job->Execute();

		if (m_JobCounts.fetch_sub(jobCounts) == jobCounts)
			 break;

		// 위에서 break가 안되었으면 다른쓰레드가 fetch_add를 해놓고 m_Jobs.Push를 못한상태임
		// 그Job을 Push할 수 있게 잠깐 cpu점유를 놓아준다.
		this_thread::yield();
	}
}
