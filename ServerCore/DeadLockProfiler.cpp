#include "pch.h"
#include "DeadLockProfiler.h"


/*-------------------------
	DeadLock Profiler
-------------------------*/

void DeadLockProfiler::PushLock(const char* name)
{
	LockGuard guard(_lock);
	int32 lockId = 0;

	auto itr = m_NameToId.find(name);
	if (itr == m_NameToId.end())
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
		// ������ �߰ߵ��� ���� ���̽���� ����� ���� Ȯ��
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

	int32 lockId = m_NameToId[name];
	if (LLockStack.top() != lockId)
		CRASH("INVALID_UNLOCK");

	LLockStack.pop();
}

void DeadLockProfiler::CheckCycle()
{
	const int32 lockCount = static_cast<int32>(m_NameToId.size());
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

void DeadLockProfiler::Dfs(int32 here)
{
	if (m_DiscoveredOrder[here] != -1)
		return;

	m_DiscoveredOrder[here] = m_DiscoveredCount++;

	// ��� ������ ������ ��ȸ�Ѵ�.
	auto itr = m_LockHistory.find(here);
	if (itr == m_LockHistory.end())
	{
		m_Finished[here] = true;
		return;
	}

	set<int32>& nextSet = itr->second;
	for (int32 there : nextSet)
	{
		//���� �湮�� ���� ���ٸ� �湮�Ѵ�.
		if (m_DiscoveredOrder[there] == -1)
		{
			m_Parent[there] = here;
			Dfs(there);
			continue;
		}

		//here�� there���� ���� �߰ߵǾ��ٸ�, there�� here�� �ļ��̴�. (�����Ⱓ��)
		if (m_DiscoveredOrder[here] < m_DiscoveredOrder[there])
			continue;

		// �������� �ƴϰ�, Dfs(there)�� ���� �������� �ʾҴٸ�, there�� here�� ������. (������ ����)
		if (m_Finished[there] == false)
		{
			printf("%s -> %s\n", m_IdToName[here], m_IdToName[there]);

			int32 now = here;
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

	m_Finished[here] = true;
}