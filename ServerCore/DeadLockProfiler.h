#pragma once

#include <stack>
#include <map>
#include <vector>


/*-------------------------
	DeadLock Profiler
-------------------------*/

class DeadLockProfiler
{
public:
	void PushLock(const char* name);
	void PopLock(const char* name);
	void CheckCycle();

private:
	void Dfs(int32 index);

private:
	unordered_map<const char*, int32>	m_NameToId;
	unordered_map<int32, const char*>	m_IdToName;
	map<int32, set<int32>>				m_LockHistory;

	Mutex _lock;

private:
	vector<int32>	m_DiscoveredOrder; //노드가 발견된 순서를 기록하는 배열
	int32			m_DiscoveredCount = 0; //노드가 발견된 순서
	vector<bool>	m_Finished; //DFS가 완료되었는지에 대한 여부
	vector<int32>	m_Parent;


};

