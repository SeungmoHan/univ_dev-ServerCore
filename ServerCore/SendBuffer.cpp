#include "pch.h"
#include "SendBuffer.h"


/*------------------
	 SendBuffer
------------------*/

SendBuffer::SendBuffer(const SendBufferChunkPtr owner, BYTE* buffer, const uint32 allocSize)
	: m_Buffer(buffer), m_AllocSize(allocSize), m_Owner(owner)
{
}

SendBuffer::~SendBuffer()
{
}

BYTE* SendBuffer::Buffer() const { return m_Buffer; }

uint32 SendBuffer::AllocSize() const
{
	return m_AllocSize;
}

uint32 SendBuffer::WriteSize() const { return m_WriteSize; }

void SendBuffer::Close(const uint32 writeSize)
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

SendBufferPtr SendBufferChunk::Open(uint32 allocSize)
{
	ASSERT_CRASH(allocSize <= SEND_BUFFER_CHUNK_SIZE);
	ASSERT_CRASH(m_Open == false);

	if (allocSize > FreeSize())
		return nullptr;

	m_Open = true;
	return ObjectPool<SendBuffer>::MakeShared(shared_from_this(), Buffer(), allocSize);
}

void SendBufferChunk::Close(const uint32 writeSize)
{
	ASSERT_CRASH(m_Open == true);

	m_Open = false;
	m_UsedSize += writeSize;
}

bool SendBufferChunk::IsOpen() const { return m_Open; }

BYTE* SendBufferChunk::Buffer() { return &m_Buffer[m_UsedSize]; }

uint32 SendBufferChunk::FreeSize() const { return static_cast<uint32>(m_Buffer.size()) - m_UsedSize; }


/*------------------------
	 SendBufferManager
------------------------*/

SendBufferPtr SendBufferManager::Open(const uint32 size)
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

	return LSendBufferChunk->Open(size);
}

SendBufferChunkPtr SendBufferManager::Pop()
{
	{
		WRITE_LOCK;
		if (m_SendBufferChunks.empty() == false)
		{
			SendBufferChunkPtr sendBufferChunk = m_SendBufferChunks.back();
			m_SendBufferChunks.pop_back();
			return sendBufferChunk;
		}
	}
	return SendBufferChunkPtr(xnew<SendBufferChunk>(), PushGlobal);
}

void SendBufferManager::Push(const SendBufferChunkPtr buffer)
{
	WRITE_LOCK;
	m_SendBufferChunks.push_back(buffer);
}

void SendBufferManager::PushGlobal(SendBufferChunk* buffer)
{
	
	g_SendBufferManager->Push(SendBufferChunkPtr(buffer, PushGlobal));
}

