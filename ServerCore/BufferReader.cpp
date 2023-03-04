#include "pch.h"
#include "BufferReader.h"


/*---------------
   BufferReader
 --------------*/
BufferReader::BufferReader()
{
}

BufferReader::BufferReader(BYTE* buffer, uint32 size, uint32 pos)
{
}

BufferReader::~BufferReader()
{
}

BYTE* BufferReader::Buffer() const { return m_Buffer; }

uint32 BufferReader::Size() const { return m_Size; }

uint32 BufferReader::ReadSize() const { return m_Pos; }

uint32 BufferReader::FreeSize() const { return m_Size - m_Pos; }
