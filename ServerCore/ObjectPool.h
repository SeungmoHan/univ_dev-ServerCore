#pragma once
#include "Types.h"
#include "MemoryPool.h"


template <typename Type>
class ObjectPool
{
public:
	template <typename... Args>
	static Type* Pop(Args&&...arg)
	{
#ifdef _STOMP
		MemoryHeader* ptr = reinterpret_cast<MemoryHeader*>(StompAllocator::Alloc(s_allocSize));
		Type* memory = static_cast<Type*>(MemoryHeader::AttachHeader(ptr, s_allocSize));
#else
		Type* memory = static_cast<Type*>(MemoryHeader::AttachHeader(s_pool.Pop(), s_allocSize));
#endif

		new(memory)Type(forward<Args>(arg)...);
		return memory;
	}

	static void Push(Type* obj)
	{
		obj->~Type();
#ifdef _STOMP
		StompAllocator::Release(MemoryHeader::DetatchHeader(obj));
#else
		s_pool.Push(MemoryHeader::DetatchHeader(obj));
#endif
	}

	template<typename...Args>
	static shared_ptr<Type> MakeShared(Args&&...args)
	{
		shared_ptr<Type> ptr = { Pop(std::forward<Args>(args)...), Push };
		return ptr;
	}

private:
	static int32		s_allocSize;
	static MemoryPool	s_pool;
};



template <typename Type>
int32 ObjectPool<Type>::s_allocSize = sizeof(Type) + sizeof(MemoryHeader);


template <typename Type>
MemoryPool ObjectPool<Type>::s_pool(s_allocSize);