// ReSharper disable CppMemberFunctionMayBeStatic
#pragma once

/*--------------------
	Base Allocator
--------------------*/

class BaseAllocator
{
public:
	static void*	Alloc(int32 size);
	static void		Release(void* ptr);
};

/*--------------------
	Stomp Allocator
--------------------*/

class StompAllocator
{
	enum { PAGE_SIZE = 4096 };
public:
	static void*	Alloc(int32 size);
	static void		Release(void* ptr);
};


/*--------------------
	Pool Allocator
--------------------*/
class PoolAllocator
{
	enum { PAGE_SIZE = 4096 };
public:
	static void*	Alloc(int32 size);
	static void		Release(void* ptr);
};


/*--------------------
	STL Allocator
--------------------*/

template<typename T>
class _xallocator
{
public:
	using value_type = T;

	_xallocator() {};

	template<typename Other>
	_xallocator(const _xallocator<Other>&) {};

	T* allocate(const size_t count);

	void deallocate(T* ptr, size_t count);
};

template <typename T>
T* _xallocator<T>::allocate(const size_t count)
{
	const int32 size = static_cast<int32>(count * sizeof(T));

	return static_cast<T*>(PoolAllocator::Alloc(size));
}

template <typename T>
void _xallocator<T>::deallocate(T* ptr, size_t count)
{
	PoolAllocator::Release(ptr);
}
