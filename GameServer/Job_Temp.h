#pragma once


// c++ 11 apply

template<int... Remains>
struct seq
{};

template<int N, int... Remains>
struct gen_seq : gen_seq<N - 1, N - 1, Remains...>
{};

template<int... Remains>
struct gen_seq<0, Remains...> : seq<Remains...>
{};

template<typename Ret, typename... Args>
void xapply(Ret(*func)(Args...), std::tuple<Args...>& tup)
{
	xapply_helper(func, gen_seq<sizeof...(Args)>(), tup);
}

template<typename F, typename... Args, int... ls>
void xapply_helper(F func, seq<ls...>, std::tuple<Args...>& tup)
{
	(func)(std::get<ls>(tup)...);
}

template<typename T, typename Ret, typename... Args>
void xapply(T* obj, Ret(T::* func)(Args...), std::tuple<Args...>& tup)
{
	xapply_helper(obj, func, gen_seq<sizeof...(Args)>(), tup);
}


template<typename T, typename F, typename... Args, int... ls>
void xapply_helper(T* obj, F func, seq<ls...>, std::tuple<Args...>& tup)
{
	(obj->*func)(std::get<ls>(tup)...);
}




/*--------------------------

--------------------------*/
class IJob
{
public:
	virtual ~IJob() = default;
	virtual void Execute() { };
};



template<typename Ret, typename... Args>
class FuncJob :public IJob
{
	using FuncType = Ret(*)(Args...);
public:
	FuncJob(FuncType func, Args...args) :m_Func(func), m_Tuple(args...) {};
	virtual void Execute() override
	{
		//std::apply(m_Func, m_Tuple); // c++ 17
		return xapply<Ret,Args...>(m_Func, m_Tuple);
	}
private:
	FuncType m_Func;
	std::tuple<Args...> m_Tuple;
};

template<typename T,typename Ret, typename... Args>
class MemberJob : public IJob
{
	using FuncType = Ret(T::*)(Args...);
public:
	MemberJob(T*obj, FuncType func, Args...args) : m_Obj(obj), m_Func(func), m_Tuple(args...) {};
	virtual void Execute() override
	{
		//std::apply(m_Func, m_Tuple); // c++ 17
		xapply<T, Ret, Args...>(m_Obj, m_Func, m_Tuple);
	}
private:
	T* m_Obj;
	FuncType m_Func;
	std::tuple<Args...> m_Tuple;
};





class HealJob final : public IJob
{
public :
	virtual void Execute() override
	{
		//Player* p = PlayerManager::Instance()->FindPlayer(m_Target);
		//if(p == nullptr) return;
		//player->heal(m_HealValue);
		cout << m_Target << " 에게 " << m_HealValue << " 만큼 회복작업" << endl;
	}

public:
	uint64 m_Target = 0;
	uint32 m_HealValue = 0;
};


using JobPtr = shared_ptr<IJob>;
using JobQ = lockfree_queue<JobPtr>;

class JobQueue
{
public:
	void Push(const JobPtr job)
	{
		WRITE_LOCK;
		m_Jobs.push(job);
	}

	JobPtr Pop()
	{
		WRITE_LOCK;
		if (m_Jobs.empty())
			return nullptr;

		JobPtr ret = m_Jobs.front();
		m_Jobs.pop();
		return ret;
	}

private:
	USE_LOCK;
	queue<JobPtr> m_Jobs;
};