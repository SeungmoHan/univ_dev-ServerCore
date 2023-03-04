#pragma once
#include <mutex>


template<typename T>
class LockQueue
{
public:
	LockQueue() {};
	LockQueue(const LockQueue&) = delete;
	LockQueue& operator= (const LockQueue&) = delete;

	void Push(T val)
	{
		lock_guard<mutex> lock(_Mutex);
		_Queue.push(std::move(val));
		_condVar.notify_one();
	}

	bool TryPop(T& ret)
	{
		lock_guard<mutex> lock(_Mutex);
		if (_Queue.empty())
			return false;

		ret = std::move(_Queue.front());
		_Queue.pop();
		return true;
	}

	void WaitPop(T& ret)
	{
		unique_lock<mutex> lock(_Mutex);
		_condVar.wait(lock, [this] { return _Queue.empty() == false; });
		ret = _Queue.front();
		_Queue.pop();
	}

private:
	queue<T> _Queue;
	mutex _Mutex;
	condition_variable _condVar;
};


template<typename T>
class lockfree_queue
{
private:
	struct Node;

	struct CountedNodePtr
	{
		int32 externalCount;
		Node* ptr = nullptr;
	};

	struct NodeCounter
	{
		uint32 internalCount : 30;
		uint32 externalCountRemaining : 2;
	};

	struct Node
	{
		Node()
		{
			NodeCounter newCount;
			newCount.internalCount = 0;
			newCount.externalCountRemaining = 2;
			count.store(newCount);

			next.ptr = nullptr;
			next.externalCount = 0;
		}

		void ReleaseRef()
		{
			NodeCounter oldCounter = count.load();

			while (true)
			{
				NodeCounter newCounter = oldCounter;
				newCounter.internalCount--;

				if (count.compare_exchange_strong(oldCounter, newCounter))
				{
					if (newCounter.internalCount == 0 && newCounter.externalCountRemaining == 0)
						delete this;

					break;
				}
			}
		}
		atomic<T*> data;
		atomic<NodeCounter> count;
		CountedNodePtr next;
	};

public:
	lockfree_queue(const lockfree_queue&) = delete;
	lockfree_queue& operator=(const lockfree_queue&) = delete;

	lockfree_queue()
	{
		CountedNodePtr node;
		node.ptr = new Node;
		node.externalCount = 1;
		m_Head.store(node);
		m_Tail.store(node);
	}

	void push(const T& value)
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

	shared_ptr<T> try_pop()
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

private:
	static void IncreaseExternalCount(atomic<CountedNodePtr>& counter, CountedNodePtr& oldCounter)
	{
		while (true)
		{
			CountedNodePtr newCounter = oldCounter;
			newCounter.externalCount++;

			if (counter.compare_exchange_strong(oldCounter, newCounter))
			{
				oldCounter.externalCount = newCounter.externalCount;
				break;
			}
		}
	}

	static void FreeExternalCount(CountedNodePtr& oldNodePtr)
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



private:
	atomic<CountedNodePtr> m_Head;
	atomic<CountedNodePtr> m_Tail;
};