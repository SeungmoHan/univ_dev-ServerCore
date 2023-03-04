#pragma once
#include "Types.h"

/*----------------
    RW SpinLock
-----------------*/

/*--------------------------------------------
[WWWWWWWW][WWWWWWWW][RRRRRRRR][RRRRRRRR]
W : WriteFlag (Exclusive Lock Owner ThreadId)
R : ReadFlag (Shared Lock Count)
---------------------------------------------*/

class Lock
{
    enum : uint32
    {
        ACQUIRE_TIMEOUT_TICK = 10000,
        MAX_SPIN_COUNT = 5000,
        WRITE_THREAD_MASK = 0xFFFF'0000,
        READ_COUNT_MASK = 0x0000'FFFF,
        EMPTY_FLAG = 0x0000'0000
    };

public:
    void WriteLock(const char* name);
    void WriteUnlock(const char* name);
    void ReadLock(const char* name);
    void ReadUnlock(const char* name);

private:
    Atomic<uint32> _lockFlag = EMPTY_FLAG;
    uint16 _writeCount = 0;
};

/*----------------
    LockGuards
-----------------*/

class ReadLockGuard
{
public:
    ReadLockGuard(Lock& lock, const char* name) : _lock(lock) ,_name(name){ _lock.ReadLock(_name); }
    ~ReadLockGuard() { _lock.ReadUnlock(_name); }

private:
    Lock& _lock;
    const char* _name;
};

class WriteLockGuard
{
public:
    WriteLockGuard(Lock& lock, const char* name) : m_Lock(lock), m_Name(name) { m_Lock.WriteLock(m_Name); }
    ~WriteLockGuard() { m_Lock.WriteUnlock(m_Name); }

private:
    Lock& m_Lock;
    const char* m_Name;
};