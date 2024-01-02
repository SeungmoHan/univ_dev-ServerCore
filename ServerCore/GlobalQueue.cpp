#include "pch.h"
#include "GlobalQueue.h"


GlobalQueue::GlobalQueue()
{
}

GlobalQueue::~GlobalQueue()
{
}

void GlobalQueue::Push(const JobSerializerPtr jobQueue)
{
	m_JobQueues.Push(jobQueue);
}

JobSerializerPtr GlobalQueue::Pop()
{
	return m_JobQueues.Pop();
}
