#include "pch.h"
#include "MemoryPool.h"


/*-------------------
	Memory Pool
-------------------*/

MemoryPool::MemoryPool(int32 allocSize) :_allocSize(allocSize)
{
	InitializeSListHead(&_header);
}

MemoryPool::~MemoryPool()
{
	MemoryHeader* header;
	while ((header = static_cast<MemoryHeader*>(InterlockedPopEntrySList(&_header))) != nullptr)
		_aligned_free(header);
}

void MemoryPool::Push(MemoryHeader* ptr)
{
	ptr->allocSize = 0;

	InterlockedPushEntrySList(&_header, static_cast<SLIST_ENTRY*>(ptr));

	_useCount.fetch_sub(1);
	_reserveCount.fetch_add(1);

}

MemoryHeader* MemoryPool::Pop()
{
	MemoryHeader* memory = static_cast<MemoryHeader*>(InterlockedPopEntrySList(&_header));

	if (memory == nullptr)
	{
		memory = reinterpret_cast<MemoryHeader*>(_aligned_malloc(_allocSize, SLIST_ALIGNMENT));
	}
	else
	{
		ASSERT_CRASH(memory->allocSize == 0);
		_reserveCount.fetch_sub(1);
	}

	_useCount.fetch_add(1);

	return memory;
}
