#include "pch.h"
#include "SendBuffer.h"


/*------------------
	 SendBuffer
------------------*/

SendBuffer::SendBuffer(SendBufferChunkRef owner, BYTE* buffer, uint32 allocSize)
	: m_Buffer(buffer), m_Owner(owner), m_AllocSize(allocSize)
{
}

SendBuffer::~SendBuffer()
{
}

void SendBuffer::Close(uint32 writeSize)
{
	ASSERT_CRASH(m_AllocSize >= writeSize);

	m_WriteSize = writeSize;
	m_Owner->Close(writeSize);
}


/*----------------------
	 SendBufferChunk
----------------------*/

SendBufferChunk::SendBufferChunk()
{
}

SendBufferChunk::~SendBufferChunk()
{
}

void SendBufferChunk::Reset()
{
	m_Open = false;
	m_UsedSize = 0;
}

SendBufferRef SendBufferChunk::Open(uint32 allocSize)
{
	ASSERT_CRASH(allocSize <= SEND_BUFFER_CHUNK_SIZE);
	ASSERT_CRASH(m_Open == false);

	if (allocSize > FreeSize())
		return nullptr;

	m_Open = true;
	return ObjectPool<SendBuffer>::MakeShared(shared_from_this(), Buffer(), allocSize);
}

void SendBufferChunk::Close(uint32 writeSize)
{
	ASSERT_CRASH(m_Open == true);

	m_Open = false;
	m_UsedSize += writeSize;
}




/*------------------------
	 SendBufferManager
------------------------*/

SendBufferRef SendBufferManager::Open(uint32 size)
{
	if (LSendBufferChunk == nullptr)
	{
		LSendBufferChunk = Pop();
		LSendBufferChunk->Reset();
	}

	ASSERT_CRASH(LSendBufferChunk->IsOpen() == false);
	
	if (LSendBufferChunk->FreeSize() < size)
	{
		LSendBufferChunk = Pop();
		LSendBufferChunk->Reset();
	}

	cout << "Free : " << LSendBufferChunk->FreeSize() << endl;

	return LSendBufferChunk->Open(size);
}

SendBufferChunkRef SendBufferManager::Pop()
{
	{
		WRITE_LOCK;
		if (m_SendBufferChunks.empty() == false)
		{
			SendBufferChunkRef sendBufferChunk = m_SendBufferChunks.back();
			m_SendBufferChunks.pop_back();
			return sendBufferChunk;
		}
	}


	return SendBufferChunkRef(xnew<SendBufferChunk>(), PushGlobal);
}

void SendBufferManager::Push(SendBufferChunkRef buffer)
{
	WRITE_LOCK;
	m_SendBufferChunks.push_back(buffer);
}

void SendBufferManager::PushGlobal(SendBufferChunk* buffer)
{
	g_SendBufferManager->Push(SendBufferChunkRef(buffer, PushGlobal));
}

