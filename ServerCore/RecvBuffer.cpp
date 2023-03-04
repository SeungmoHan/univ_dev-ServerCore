#include "pch.h"
#include "RecvBuffer.h"


/*---------------
	RecvBuffer
---------------*/
RecvBuffer::RecvBuffer(const uint32 bufferSize) : m_BufferSize(bufferSize), m_Capacity(bufferSize* BUFFER_COUNT)
{
	m_Buffer.resize(m_Capacity);
}

RecvBuffer::~RecvBuffer()
{
}

void RecvBuffer::Clean()
{
	uint32 dataSize = DataSize();
	if (dataSize == 0)
	{
		m_ReadPos = m_WritePos = 0;
		return;
	}
	if (FreeSize() < m_BufferSize)
	{
		memcpy_s(&m_Buffer[0], dataSize, &m_Buffer[m_ReadPos], dataSize);
		m_ReadPos = 0;
		m_WritePos = dataSize;
	}
}

bool RecvBuffer::OnWrite(const uint32 numOfBytes)
{
	if (numOfBytes > FreeSize())
		return false;

	m_WritePos += numOfBytes;

	return true;
}

bool RecvBuffer::OnRead(const uint32 numOfBytes)
{
	if (numOfBytes > DataSize())
		return false;

	m_ReadPos += numOfBytes;

	return true;
}
