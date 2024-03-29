#pragma once
#include <mutex>



template<typename T>
class LockQueue_Test
{
public:
	LockQueue_Test();;
	LockQueue_Test(const LockQueue_Test&) = delete;
	LockQueue_Test& operator= (const LockQueue_Test&) = delete;

	void Push(T val);

	bool TryPop(T& ret);

	void WaitPop(T& ret);

private:
	queue<T> m_Queue;
	mutex m_Mutex;
	condition_variable m_ConditionVar;
};


template<typename T>
class lockfree_queue
{
private:
	struct Node;

	struct CountedNodePtr
	{
		int32 externalCount{};
		Node* ptr = nullptr;
	};

	struct NodeCounter
	{
		uint32 internalCount : 30;
		uint32 externalCountRemaining : 2;
	};

	struct Node
	{
		Node();

		void ReleaseRef();
		atomic<T*> data;
		atomic<NodeCounter> count;
		CountedNodePtr next;
	};

public:
	lockfree_queue(const lockfree_queue&) = delete;
	lockfree_queue& operator=(const lockfree_queue&) = delete;

	lockfree_queue();

	void push(const T& value);

	shared_ptr<T> try_pop();

private:
	static void IncreaseExternalCount(atomic<CountedNodePtr>& counter, CountedNodePtr& oldCounter);

	static void FreeExternalCount(CountedNodePtr& oldNodePtr);

private:
	atomic<CountedNodePtr> m_Head;
	atomic<CountedNodePtr> m_Tail;
};

template <typename T>
LockQueue_Test<T>::LockQueue_Test()
{}

template <typename T>
void LockQueue_Test<T>::Push(T val)
{
	lock_guard<mutex> lock(m_Mutex);
	m_Queue.push(std::move(val));
	m_ConditionVar.notify_one();
}

template <typename T>
bool LockQueue_Test<T>::TryPop(T& ret)
{
	lock_guard<mutex> lock(m_Mutex);
	if (m_Queue.empty())
		return false;

	ret = std::move(m_Queue.front());
	m_Queue.pop();
	return true;
}

template <typename T>
void LockQueue_Test<T>::WaitPop(T& ret)
{
	unique_lock<mutex> lock(m_Mutex);
	m_ConditionVar.wait(lock, [this] { return m_Queue.empty() == false; });
	ret = m_Queue.front();
	m_Queue.pop();
}

template <typename T>
lockfree_queue<T>::Node::Node()
{
	NodeCounter newCount;
	newCount.internalCount = 0;
	newCount.externalCountRemaining = 2;
	count.store(newCount);

	next.ptr = nullptr;
	next.externalCount = 0;
}

template <typename T>
void lockfree_queue<T>::Node::ReleaseRef()
{
	NodeCounter oldCounter = count.load();

	while (true)
	{
		NodeCounter newCounter = oldCounter;
		--newCounter.internalCount;

		if (count.compare_exchange_strong(oldCounter, newCounter))
		{
			if (newCounter.internalCount == 0 && newCounter.externalCountRemaining == 0)
				delete this;

			break;
		}
	}
}

template <typename T>
lockfree_queue<T>::lockfree_queue()
{
	CountedNodePtr node;
	node.ptr = new Node;
	node.externalCount = 1;
	m_Head.store(node);
	m_Tail.store(node);
}

template <typename T>
void lockfree_queue<T>::push(const T& value)
{
	unique_ptr<T> newData = std::make_unique<T>(value);

	CountedNodePtr dummy;
	dummy.ptr = new Node();
	dummy.externalCount = 1;

	CountedNodePtr oldTail = m_Tail.load();

	while (true)
	{
		IncreaseExternalCount(m_Tail, oldTail);

		T* oldData = nullptr;
		if (oldTail.ptr->data.compare_exchange_strong(oldData, newData.get()))
		{
			oldTail.ptr->next = dummy;
			oldTail = m_Tail.exchange(dummy);
			FreeExternalCount(oldTail);
			newData.release();
			break;
		}

		oldTail.ptr->ReleaseRef();
	}
}

template <typename T>
shared_ptr<T> lockfree_queue<T>::try_pop()
{
	CountedNodePtr oldHead = m_Head.load();

	while (true)
	{
		IncreaseExternalCount(m_Head, oldHead);

		Node* ptr = oldHead.ptr;
		if (ptr == m_Tail.load().ptr)
		{
			ptr->ReleaseRef();
			return shared_ptr<T>();
		}

		if (m_Head.compare_exchange_strong(oldHead, ptr->next))
		{
			T* res = ptr->data.load();
			FreeExternalCount(oldHead);
			return shared_ptr<T>(res);
		}

		ptr->ReleaseRef();
	}
}

template <typename T>
void lockfree_queue<T>::IncreaseExternalCount(atomic<CountedNodePtr>& counter, CountedNodePtr& oldCounter)
{
	while (true)
	{
		CountedNodePtr newCounter = oldCounter;
		++newCounter.externalCount;

		if (counter.compare_exchange_strong(oldCounter, newCounter))
		{
			oldCounter.externalCount = newCounter.externalCount;
			break;
		}
	}
}

template <typename T>
void lockfree_queue<T>::FreeExternalCount(CountedNodePtr& oldNodePtr)
{
	Node* ptr = oldNodePtr.ptr;
	const int32 countIncrease = oldNodePtr.externalCount - 2;

	NodeCounter oldCounter = ptr->count.load();

	while (true)
	{
		NodeCounter newCounter = oldCounter;
		newCounter.externalCountRemaining--; //TODO
		newCounter.internalCount += countIncrease;

		if (ptr->count.compare_exchange_strong(oldCounter, newCounter))
		{
			if (newCounter.internalCount == 0 && newCounter.externalCountRemaining == 0)
				delete ptr;
			break;
		}
	}
}
