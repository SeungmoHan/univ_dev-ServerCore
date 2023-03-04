#include "pch.h"
#include "Memory.h"
#include "MemoryPool.h"

/*-------------------
		Memory 
-------------------*/

Memory::Memory()
{
	int32 size = 0;
	int32 tableIndex = 0;

	for (size = 32; size <= 1024; size += 32)
	{
		auto* pool = new MemoryPool(size);
		_pool.push_back(pool);

		while (tableIndex <= size)
		{
			_poolTable[tableIndex] = pool;
			tableIndex++;
		}
	}

	for (; size <= 2048; size += 128)
	{
		auto* pool = new MemoryPool(size);
		_pool.push_back(pool);

		while (tableIndex <= size)
		{
			_poolTable[tableIndex] = pool;
			tableIndex++;
		}
	}

	for (; size <= 4096; size += 256)
	{
		auto* pool = new MemoryPool(size);
		_pool.push_back(pool);

		while (tableIndex <= size)
		{
			_poolTable[tableIndex] = pool;
			tableIndex++;
		}
	}
}

Memory::~Memory()
{
	for (const MemoryPool* pool : _pool)
	{
		delete pool;
	}
	_pool.clear();
}

void* Memory::Allocate(const int32 size) const
{
	MemoryHeader* header = nullptr;

	const int32 allocSize = size + sizeof(MemoryHeader);
#ifdef _STOMP
	header = reinterpret_cast<MemoryHeader*>(StompAllocator::Alloc(allocSize));
#else
	if (allocSize > MAX_ALLOC_SIZE)
	{
		header = static_cast<MemoryHeader*>(_aligned_malloc(allocSize, SLIST_ALIGNMENT));
	}
	else
	{
		header = _poolTable[allocSize]->Pop();
	}
#endif

	return MemoryHeader::AttachHeader(header, allocSize);
}

void Memory::Release(void* ptr) const
{
	MemoryHeader* header = MemoryHeader::DetatchHeader(ptr);

	const int32 allocSize = header->allocSize;
	ASSERT_CRASH(allocSize > 0);

#ifdef _STOMP
	StompAllocator::Release(ptr);
#else
	if (allocSize > MAX_ALLOC_SIZE)
	{
		_aligned_free(header);
	}
	else
	{
		_poolTable[allocSize]->Push(header);
	}
#endif
}
