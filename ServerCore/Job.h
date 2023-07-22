#pragma once
#include <functional>

/*--------------
	   Job
 -------------*/

using CallbackType = std::function<void()>;

class Job
{
public:
	Job(CallbackType&& callback) : m_Callback(std::move(callback)){}

	template<typename T, typename Ret, typename... Args>
	Job(shared_ptr<T> owner, Ret(T::*memFunc)(Args...), Args&&... args)
	{
		m_Callback = [owner, memFunc, args...]()
		{
			(owner.get()->*memFunc)(args...);
		};
	}

	void Execute()
	{
		m_Callback();
	}

private:
	CallbackType m_Callback;
};

