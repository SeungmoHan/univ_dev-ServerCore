#include "pch.h"
#include "DeadLockProfiler.h"


/*-------------------------
	DeadLock Profiler
-------------------------*/

void DeadLockProfiler::PushLock(const char* name)
{
	LockGuard guard(_lock);
	int32 lockId = 0;

	if (const auto itr = m_NameToId.find(name); itr == m_NameToId.end())
	{
		lockId = static_cast<int32>(m_NameToId.size());
		m_NameToId[name] = lockId;
		m_IdToName[lockId] = name;
	}
	else
	{
		lockId = itr->second;
	}

	if (!LLockStack.empty())
	{
		// 기존에 발견되지 않은 케이스라면 데드락 여부 확인
		const int32 prevId = LLockStack.top();
		if (lockId != prevId)
		{
			set<int32>& history = m_LockHistory[prevId];
			if (history.find(lockId) == history.end())
			{
				history.insert(lockId);
				CheckCycle();
			}
		}
	}
	LLockStack.push(lockId);
}

void DeadLockProfiler::PopLock(const char* name)
{
	LockGuard guard(_lock);

	if (LLockStack.empty())
		CRASH("MULTIPLE_UNLOCK");

	if (const int32 lockId = m_NameToId[name]; LLockStack.top() != lockId)
		CRASH("INVALID_UNLOCK");

	LLockStack.pop();
}

void DeadLockProfiler::CheckCycle()
{
	const auto lockCount = static_cast<int32>(m_NameToId.size());
	m_DiscoveredOrder = vector<int32>(lockCount, -1);
	m_DiscoveredCount = 0;
	m_Finished = vector<bool>(lockCount, false);
	m_Parent = vector<int32>(lockCount, -1);

	for (int32 lockId = 0; lockId < lockCount; lockId++)
		Dfs(lockId);

	m_DiscoveredOrder.clear();
	m_Finished.clear();
	m_Parent.clear();
}

void DeadLockProfiler::Dfs(const int32 index)
{
	if (m_DiscoveredOrder[index] != -1)
		return;

	m_DiscoveredOrder[index] = m_DiscoveredCount++;

	// 모든 인접한 정점을 순회한다.
	const auto itr = m_LockHistory.find(index);
	if (itr == m_LockHistory.end())
	{
		m_Finished[index] = true;
		return;
	}

	const set<int32>& nextSet = itr->second;
	for (int32 there : nextSet)
	{
		//아직 방문한 적이 없다면 방문한다.
		if (m_DiscoveredOrder[there] == -1)
		{
			m_Parent[there] = index;
			Dfs(there);
			continue;
		}

		//here가 there보다 먼저 발견되었다면, there는 here의 후손이다. (순방향간선)
		if (m_DiscoveredOrder[index] < m_DiscoveredOrder[there])
			continue;

		// 순방향이 아니고, Dfs(there)가 아직 종료하지 않았다면, there는 here의 선조다. (역방향 간선)
		if (m_Finished[there] == false)
		{
			printf("%s -> %s\n", m_IdToName[index], m_IdToName[there]);

			int32 now = index;
			while (true)
			{
				printf("%s -> %s\n", m_IdToName[m_Parent[now]], m_IdToName[now]);
				now = m_Parent[now];
				if (now == there)
					break;
			}
			CRASH("DEADLOCK_DETECTED");
		}
	}

	m_Finished[index] = true;
}
