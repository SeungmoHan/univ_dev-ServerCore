#include "pch.h"
#include "GlobalQueue.h"


GlobalQueue::GlobalQueue()
{
}

GlobalQueue::~GlobalQueue()
{
}

void GlobalQueue::Push(const JobSerializerRef jobQueue)
{
	m_JobQueues.Push(jobQueue);
}

JobSerializerRef GlobalQueue::Pop()
{
	return m_JobQueues.Pop();
}
