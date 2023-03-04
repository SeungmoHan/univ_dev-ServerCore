#include "pch.h"
#include "BufferWriter.h"


/*---------------
   BufferReader
 --------------*/
BufferWriter::BufferWriter() = default;

BufferWriter::BufferWriter(BYTE* buffer, const uint32 size, const uint32 pos)
	:m_Buffer(buffer), m_Size(size), m_Pos(pos)
{
}

BufferWriter::~BufferWriter() = default;

BYTE* BufferWriter::Buffer() const { return m_Buffer; }

uint32 BufferWriter::Size() const { return m_Size; }

uint32 BufferWriter::WriteSize() const { return m_Pos; }

uint32 BufferWriter::FreeSize() const { return m_Size - m_Pos; }


bool BufferWriter::Write(const void* src, const uint32 len)
{
	if (FreeSize() < len)
		return false;
	memcpy_s(&m_Buffer[m_Pos], len, src, len);
	m_Pos += len;
	return true;
}
