#pragma once
#include "Job.h"
#include "LockQueue.h"


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


	//혹시나 모를 잡shared_ptr 사이클 방지를 위한 안전책
	void ClearJob() { m_Jobs.ClearJob(); }

protected:
	LockQueue<JobRef>	m_Jobs;
	Atomic<int32>		m_JobCounts = 0;
private:
	void Push(JobRef&& job);
	void Execute();
};
