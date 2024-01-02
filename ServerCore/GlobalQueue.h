#pragma once

/*----------------
	GlobalQueue
----------------*/


class GlobalQueue
{
public:
	GlobalQueue();
	~GlobalQueue();

	void		Push(JobSerializerPtr jobQueue);
	JobSerializerPtr Pop();

private:
	LockQueue<JobSerializerPtr> m_JobQueues;
};
