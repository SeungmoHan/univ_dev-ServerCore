#pragma once


/*---------------
   BufferReader
 --------------*/

class BufferReader
{
public:
	BufferReader();
	BufferReader(BYTE* buffer, uint32 size, uint32 pos = 0);
	~BufferReader();

	BYTE* Buffer()const;
	uint32 Size() const;
	uint32 ReadSize() const;
	uint32 FreeSize() const;

	template<typename T>
	bool Peek(T* dest);

	template<typename T>
	bool Read(T* dest);

	bool Peek(void* dest, const uint32 len) const;
	bool Read(void* dest, const uint32 len);

	template<typename T>
	BufferReader& operator>>(OUT T& dest);

private:

	BYTE*	m_Buffer = nullptr;
	uint32	m_Size = 0;
	uint32	m_Pos = 0;
};




template <typename T>
bool BufferReader::Peek(T* dest)
{
	return Peek(dest, sizeof(T));
}

template <typename T>
bool BufferReader::Read(T* dest)
{
	return Read(dest, sizeof(T));
}

template <typename T>
BufferReader& BufferReader::operator>>(OUT T& dest)
{
	dest = *reinterpret_cast<T*>(&m_Buffer[m_Pos]);
	m_Pos += sizeof(T);
	return *this;
}
