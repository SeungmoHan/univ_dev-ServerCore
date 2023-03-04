#include "pch.h"
#include "BufferReader.h"


/*---------------
   BufferReader
 --------------*/
BufferReader::BufferReader() = default;

BufferReader::BufferReader(BYTE* buffer, uint32 size, uint32 pos)
{
}

BufferReader::~BufferReader() = default;

BYTE* BufferReader::Buffer() const { return m_Buffer; }

uint32 BufferReader::Size() const { return m_Size; }

uint32 BufferReader::ReadSize() const { return m_Pos; }

uint32 BufferReader::FreeSize() const { return m_Size - m_Pos; }

bool BufferReader::Peek(const void* dest, const uint32 len) const
{
	if (FreeSize() < len)
		return false;
	memcpy_s(&m_Buffer[m_Pos], len, dest, len);
	return true;
}

bool BufferReader::Read(const void* dest, const uint32 len)
{
	if (Peek(dest, len) == false)
		return false;
	m_Pos += len;
	return true;
}
