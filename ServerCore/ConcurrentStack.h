#pragma once
#pragma once

#include <mutex>


template<typename T>
class LockStack
{
public:
	LockStack();;
	LockStack(const LockStack&) = delete;
	LockStack& operator= (const LockStack&) = delete;

	void Push(T value);

	bool Empty();

	bool TryPop(T& ret);

	void WaitPop(T& ret);

private:
	std::stack<T> m_Stack;
	std::mutex m_Mutex;
	condition_variable m_ConditionVar;
};



//template<typename T>
//class LockFreeStack
//{
//	struct Node
//	{
//		Node(const T& value) : data(std::make_shared<T>(value)), next(nullptr)
//		{
//
//		};
//		std::shared_ptr<T> data;
//		std::shared_ptr<Node> next;
//	};
//
//
//public:
//	void Push(const T& data)
//	{
//		shared_ptr<Node> newNode = make_shared<Node>(data);
//		newNode->next = std::atomic_load(&_head);
//
//		while (std::atomic_compare_exchange_weak(&_head, &newNode->next, newNode) == false);
//	}
//
//	shared_ptr<T> TryPop()
//	{
//		shared_ptr<Node> oldHead = std::atomic_load(&_head);
//
//		while (oldHead && std::atomic_compare_exchange_weak(&_head, &oldHead, oldHead->next) == false);
//
//		if (oldHead == nullptr)
//			return shared_ptr<T>();
//
//		return oldHead->data;
//	}
//private:
//
//private:
//	shared_ptr<Node> _head;
//};

template <typename T>
LockStack<T>::LockStack()
{}

template <typename T>
void LockStack<T>::Push(T value)
{
	lock_guard<mutex> lock(m_Mutex);
	m_Stack.push(std::move(value));
	m_ConditionVar.notify_one();
}

template <typename T>
bool LockStack<T>::Empty()
{
	lock_guard<mutex> lock(m_Mutex);
	return m_Stack.empty();
}

template <typename T>
bool LockStack<T>::TryPop(T& ret)
{
	lock_guard<mutex> lock(m_Mutex);
	if (m_Stack.empty())
		return false;

	ret = std::move(m_Stack.top());
	m_Stack.pop();
	return true;
}

template <typename T>
void LockStack<T>::WaitPop(T& ret)
{
	unique_lock<mutex> lock(m_Mutex);
	m_ConditionVar.wait(lock, [this] {return m_Stack.empty() == false; });
	ret = std::move(m_Stack.top());
	m_Stack.pop();
}

template<typename T>
class lockfree_stack
{
private:
	struct Node;
	struct CountedNodePtr
	{
		int32 externalCount = 0;
		Node* ptr = nullptr;
	};
	struct Node
	{
		Node(const T& value) : data(std::make_shared<T>(value))
		{

		};
		std::shared_ptr<T> data;
		atomic<int32> internalCount = 0;
		CountedNodePtr next;
	};


public:
	void push(const T& data)
	{
		CountedNodePtr newNode;
		newNode.ptr = new Node(data);
		newNode.externalCount = 1;

		newNode.ptr->next = m_Head;
		while (m_Head.compare_exchange_weak(newNode.ptr->next, newNode) == false);

	}

	shared_ptr<T> try_pop()
	{
		CountedNodePtr oldHead = m_Head;
		while (true)
		{
			increase_head_count(oldHead);

			Node* ptr = oldHead.ptr;

			if (ptr == nullptr)
				return shared_ptr<T>();

			if (m_Head.compare_exchange_strong(oldHead, ptr->next))
			{
				shared_ptr<T> res;

				res.swap(ptr->data);

				const int32 countIncrease = oldHead.externalCount - 2;

				if (ptr->internalCount.fetch_add(countIncrease) == -countIncrease)
					delete ptr;

				return res;
			}
			else if (ptr->internalCount.fetch_sub(1) == 1)
			{
				delete ptr;
			}
		}
	}
private:
	void increase_head_count(CountedNodePtr& oldCounter)
	{
		while (true)
		{
			CountedNodePtr newCounter = oldCounter;
			++newCounter.externalCount;

			if (m_Head.compare_exchange_strong(oldCounter, newCounter))
			{
				oldCounter.externalCount = newCounter.externalCount;
				break;
			}
		}
	}
private:
	atomic<CountedNodePtr> m_Head;
};
