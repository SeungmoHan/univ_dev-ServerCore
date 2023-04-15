#pragma once





/*------------------
		Lock
------------------*/
#pragma region LOCK_IN_CLASS
#define USE_MANY_LOCKS(count)	Lock _locks[count];
#define USE_LOCK				USE_MANY_LOCKS(1)
#define	READ_LOCK_IDX(idx)		ReadLockGuard readLockGuard_##idx(_locks[idx],typeid(this).name());
#define READ_LOCK				READ_LOCK_IDX(0)
#define	WRITE_LOCK_IDX(idx)		WriteLockGuard writeLockGuard_##idx(_locks[idx],typeid(this).name());
#define WRITE_LOCK				WRITE_LOCK_IDX(0)
#pragma endregion

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
#pragma region CRASH_DEFINE
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
#pragma endregion


/*------------------
		 LOG
------------------*/
#pragma region LOG_DEFINE
#define DUMMY_ERR_LOG Logger(ServerType::DUMMY_CLIENT, LoggerType::ERROR_LOG)
#define DUMMY_WAR_LOG Logger(ServerType::DUMMY_CLIENT, LoggerType::WARNING_LOG)
#define DUMMY_DEV_LOG Logger(ServerType::DUMMY_CLIENT, LoggerType::DEBUG_LOG)
#define DUMMY_LOG Logger(ServerType::DUMMY_CLIENT)

#define GAME_ERR_LOG Logger(ServerType::GAME_SERVER, LoggerType::ERROR_LOG)
#define GAME_WAR_LOG Logger(ServerType::GAME_SERVER, LoggerType::WARNING_LOG)
#define GAME_DEV_LOG Logger(ServerType::GAME_SERVER, LoggerType::DEBUG_LOG)
#define GAME_LOG Logger(ServerType::GAME_SERVER)

#define DB_ERR_LOG Logger(ServerType::DB_SERVER, LoggerType::ERROR_LOG)
#define DB_WAR_LOG Logger(ServerType::DB_SERVER, LoggerType::WARNING_LOG)
#define DB_DEV_LOG Logger(ServerType::DB_SERVER, LoggerType::DEBUG_LOG)
#define DB_LOG Logger(ServerType::DB_SERVER)
#pragma endregion

#pragma region ETC_DEFINE
#define OUT
#define IN
#pragma endregion