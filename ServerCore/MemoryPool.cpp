#include "pch.h"
#include "MemoryPool.h"


/*-------------------
	Memory Pool
-------------------*/

MemoryPool::MemoryPool(const int32 allocSize) :m_AllocSize(allocSize)
{
	InitializeSListHead(&m_Header);
}

MemoryPool::~MemoryPool()
{
	MemoryHeader* header;
	while ((header = static_cast<MemoryHeader*>(InterlockedPopEntrySList(&m_Header))) != nullptr)
		_aligned_free(header);
}

void MemoryPool::Push(MemoryHeader* ptr)
{
	ptr->allocSize = 0;

	InterlockedPushEntrySList(&m_Header, static_cast<SLIST_ENTRY*>(ptr));

	m_UseCount.fetch_sub(1);
	m_ReserveCount.fetch_add(1);

}

MemoryHeader* MemoryPool::Pop()
{
	auto* memory = static_cast<MemoryHeader*>(InterlockedPopEntrySList(&m_Header));

	if (memory == nullptr)
	{
		memory = static_cast<MemoryHeader*>(_aligned_malloc(m_AllocSize, SLIST_ALIGNMENT));
	}
	else
	{
		ASSERT_CRASH(memory->allocSize == 0);
		m_ReserveCount.fetch_sub(1);
	}

	m_UseCount.fetch_add(1);

	return memory;
}
