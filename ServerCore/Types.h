#pragma once
#include <mutex>
#include <atomic>

using BYTE 		= unsigned char;
using int8		= __int8;
using int16		= __int16;
using int32		= __int32;
using int64		= __int64;
using uint8		= unsigned __int8;
using uint16	= unsigned __int16;
using uint32	= unsigned __int32;
using uint64	= unsigned __int64;

template<typename T>
using Atomic				= std::atomic<T>;
using Mutex					= std::mutex;
using CondVar				= std::condition_variable;
using UniqueLock			= std::unique_lock<std::mutex>;
using LockGuard				= std::lock_guard<std::mutex>;

template<typename T>
using ref = std::shared_ptr<T>;

#define SHARED_REF(_Typename) \
	using _Typename##Ptr = ::ref<class _Typename>;

SHARED_REF(IocpCore);
SHARED_REF(IocpObject);
SHARED_REF(PacketSession);
SHARED_REF(Session);
SHARED_REF(Listener);
SHARED_REF(ServerService);
SHARED_REF(ClientService);

SHARED_REF(SendBuffer);
SHARED_REF(SendBufferChunk);

SHARED_REF(Job);
SHARED_REF(JobSerializer);


#define size16(val)		static_cast<int16>(sizeof(val))
#define size32(val)		static_cast<int32>(sizeof(val))
#define len16(arr)		static_cast<int16>(sizeof(arr) / sizeof(arr[0]))
#define len32(arr)		static_cast<int32>(sizeof(arr) / sizeof(arr[0]))

//#define _STOMP