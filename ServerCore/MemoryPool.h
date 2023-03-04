#pragma once

enum
{
	SLIST_ALIGNMENT = 16,
};

/*--------------------
	Memory Header
--------------------*/
DECLSPEC_ALIGN(SLIST_ALIGNMENT)
struct MemoryHeader : public SLIST_ENTRY
{
	explicit MemoryHeader(const int32 size) : _SLIST_ENTRY(), allocSize(size){}

	static void* AttachHeader(MemoryHeader* header, const int32 size)
	{
		new(header)MemoryHeader(size);
		return reinterpret_cast<void*>(++header);
	}

	static MemoryHeader* DetatchHeader(void* ptr)
	{
		MemoryHeader* header = static_cast<MemoryHeader*>(ptr) - 1;
		return header;
	}

	int32 allocSize;
};

/*-------------------
	Memory Pool
-------------------*/

DECLSPEC_ALIGN(SLIST_ALIGNMENT)
class MemoryPool
{
public:
	explicit MemoryPool(int32 allocSize);
	~MemoryPool();

	void			Push(MemoryHeader* ptr);
	MemoryHeader*	Pop();

private:
	SLIST_HEADER		_header;
	int32				_allocSize = 0;
	atomic<int32>		_useCount = 0;
	atomic<int32>		_reserveCount = 0;
};

