#pragma once

template<typename T>
class LockQueue
{
public:
	void Push(const JobRef job)
	{
		WRITE_LOCK;
		m_Items.push(job);
	}

	T Pop()
	{
		WRITE_LOCK;
		if (m_Items.empty())
			return T();

		T ret = m_Items.front();
		m_Items.pop();
		return ret;
	}

	void PopAll(OUT Vector<T>& items)
	{
		WRITE_LOCK;
		while(T item = Pop())
		{
			items.push_back(item);
		}
	}

	void ClearJob()
	{
		WRITE_LOCK;
		m_Items = Queue<T>();
	}

private:
	USE_LOCK;
	Queue<T> m_Items;
};