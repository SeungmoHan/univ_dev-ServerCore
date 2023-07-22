#pragma once
#include "Job.h"
#include "JobQueue.h"


/*---------------
  JobSerializer
 --------------*/

class JobSerializer : public enable_shared_from_this<JobSerializer>
{
public:
	void PushJob(CallbackType&& callback)
	{
		auto job = ObjectPool<Job>::MakeShared(std::move(callback));
		m_JobQueue.Push(job);
	}

	template<typename T, typename Ret, typename... Args>
	void PushJob(Ret(T::*memFunc)(Args...), Args... args)
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		auto job = ObjectPool<Job>::MakeShared(owner, memFunc, std::forward<Args>(args)...);
		m_JobQueue.Push(job);
	}

	virtual void FlushJob() abstract;

protected:
	JobQueue m_JobQueue;
};
