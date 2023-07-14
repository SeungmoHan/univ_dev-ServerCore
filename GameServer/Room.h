#pragma once
#include <utility>

#include "Job.h"

class Room
{
public:
	void Enter(PlayerRef player);
	void Leave(PlayerRef player);
	void Broadcast(SendBufferRef sendBuffer);

	// multi thread 환경에서의 작업
public:
	//void PushJob(JobRef job) { m_Jobs.Push(std::move(job)); }
	void FlushJob();

	template<typename T, typename Ret, typename... Args>
	void PushJob(Ret(T::* memFunc)(Args...), Args... args);

private:
	USE_LOCK;
	map<uint64, PlayerRef> m_PlayerMap;

	JobQueue m_Jobs;
	Atomic<bool> m_UseFlag = false;
};

template <typename T, typename Ret, typename ... Args>
void Room::PushJob(Ret(T::* memFunc)(Args...), Args... args)
{
	auto job = MakeShared<MemberJob<T, Ret, Args...>>(static_cast<T*>(this), memFunc, args...);
	m_Jobs.Push(job);
}

extern Room g_Room;
