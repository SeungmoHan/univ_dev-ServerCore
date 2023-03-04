#pragma once





/*------------------
		Lock
------------------*/

#define USE_MANY_LOCKS(count)	Lock _locks[count];
#define USE_LOCK				USE_MANY_LOCKS(1)
#define	READ_LOCK_IDX(idx)		ReadLockGuard readLockGuard_##idx(_locks[idx],typeid(this).name());
#define READ_LOCK				READ_LOCK_IDX(0)
#define	WRITE_LOCK_IDX(idx)		WriteLockGuard writeLockGuard_##idx(_locks[idx],typeid(this).name());
#define WRITE_LOCK				WRITE_LOCK_IDX(0)

///*------------------
//	   Memory
//------------------*/
//
//#ifdef _DEBUG
//#define _xalloc(size)	PoolAllocator::Alloc(size)
//#define _xrelease(ptr)	PoolAllocator::Release(ptr)
//#else
//#define _xalloc(size)	PoolAllocator::Alloc(size)
//#define _xrelease(ptr)	PoolAllocator::Release(ptr)
//#endif



/*------------------
		CRASH
------------------*/


#define CRASH(cause)					\
do{										\
	uint32* crash = nullptr;			\
	__analysis_assume(crash != nullptr);\
	*crash = 100;						\
}while(0)


#define ASSERT_CRASH(expr)				\
do{										\
	if(!(expr))							\
	{									\
		__analysis_assume(expr);		\
		CRASH("ASSERT_CRASH");			\
	}									\
}while(0)


#define OUT
