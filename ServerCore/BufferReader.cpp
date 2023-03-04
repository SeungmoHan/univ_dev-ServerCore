#include "pch.h"
#include "BufferReader.h"


/*---------------
   BufferReader
 --------------*/
BufferReader::BufferReader() = default;

BufferReader::BufferReader(BYTE* buffer, const uint32 size, const uint32 pos)
	: m_Buffer(buffer), m_Size(size) , m_Pos(pos)
{
}

BufferReader::~BufferReader() = default;

BYTE* BufferReader::Buffer() const { return m_Buffer; }

uint32 BufferReader::Size() const { return m_Size; }

uint32 BufferReader::ReadSize() const { return m_Pos; }

uint32 BufferReader::FreeSize() const { return m_Size - m_Pos; }

bool BufferReader::Peek(void* dest, const uint32 len) const
{
	if (FreeSize() < len)
		return false;
	memcpy_s(dest, len, &m_Buffer[m_Pos], len);
	return true;
}

bool BufferReader::Read(void* dest, const uint32 len)
{
	if (Peek(dest, len) == false)
		return false;
	m_Pos += len;
	return true;
}
