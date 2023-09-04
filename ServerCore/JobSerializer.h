#pragma once
#include "Job.h"
#include "JobTimer.h"
#include "LockQueue.h"
#include "JobTimer.h"


/*---------------
  JobSerializer
 --------------*/

class JobSerializer : public enable_shared_from_this<JobSerializer>
{
public:
	void DoAsync(CallbackType&& callback)
	{
		Push(ObjectPool<Job>::MakeShared(std::move(callback)));
	}

	template<typename T, typename Ret, typename... Args>
	void DoAsync(Ret(T::*memFunc)(Args...), Args... args)
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		Push(ObjectPool<Job>::MakeShared(owner, memFunc, std::forward<Args>(args)...));
	}

	void DoTimer(uint64 tickAfter, CallbackType&& callback)
	{
		g_JobTimer->Reserve(tickAfter, shared_from_this(), (ObjectPool<Job>::MakeShared(std::move(callback))));
	}

	template<typename T, typename Ret, typename... Args>
	void DoTimer(uint64 tickAfter, Ret(T::* memFunc)(Args...), Args... args)
	{
		shared_ptr<T> owner = static_pointer_cast<T>(shared_from_this());
		auto job = ObjectPool<Job>::MakeShared(owner, memFunc, std::forward<Args>(args)...);
		g_JobTimer->Reserve(tickAfter, owner, job);
	}


	//혹시나 모를 잡shared_ptr 사이클 방지를 위한 안전책
	void ClearJob() { m_Jobs.ClearJob(); }

	void Execute();
	void Push(JobRef job, bool pushOnly = false);
protected:
	LockQueue<JobRef>	m_Jobs;
	Atomic<int32>		m_JobCounts = 0;
};
