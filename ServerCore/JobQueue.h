#pragma once


class JobQueue
{
public:
	void Push(const JobRef job)
	{
		WRITE_LOCK;
		m_Jobs.push(job);
	}

	JobRef Pop()
	{
		WRITE_LOCK;
		if (m_Jobs.empty())
			return nullptr;

		JobRef ret = m_Jobs.front();
		m_Jobs.pop();
		return ret;
	}

private:
	USE_LOCK;
	queue<JobRef> m_Jobs;
};