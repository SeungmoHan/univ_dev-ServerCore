#pragma once

/*----------------
	GlobalQueue
----------------*/


class GlobalQueue
{
public:
	GlobalQueue();
	~GlobalQueue();

	void		Push(JobSerializerRef jobQueue);
	JobSerializerRef Pop();

private:
	LockQueue<JobSerializerRef> m_JobQueues;
};
