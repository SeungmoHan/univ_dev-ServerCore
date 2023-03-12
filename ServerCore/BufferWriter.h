#pragma once
/*---------------
   BufferWriter
 --------------*/

class BufferWriter
{
public:
	BufferWriter();
	BufferWriter(BYTE* buffer, uint32 size, uint32 pos = 0);
	~BufferWriter();

	[[nodiscard]] BYTE* Buffer()const;
	[[nodiscard]] uint32 Size() const;
	[[nodiscard]] uint32 WriteSize() const;
	[[nodiscard]] uint32 FreeSize() const;

	template<typename T>
	bool Write(T* dest) { return Write(dest, sizeof(T)); }

	bool Write(const void* src, const uint32 len);

	template<typename T>
	BufferWriter& operator<<(IN const T& src);

	template<typename T>
	BufferWriter& operator<<(IN const T&& src);

	template<typename T>
	T* Reserve(const uint32 count = 1);

private:

	BYTE* m_Buffer = nullptr;
	uint32	m_Size = 0;
	uint32	m_Pos = 0;
};

template <typename T>
BufferWriter& BufferWriter::operator<<(IN const T& src)
{
	T* temp = reinterpret_cast<T*>(&m_Buffer[m_Pos]);
	*temp = src;
	m_Pos += sizeof(T);
	return *this;
}

template <typename T>
BufferWriter& BufferWriter::operator<<(const T&& src)
{
	T* temp = reinterpret_cast<T*>(&m_Buffer[m_Pos]);
	*temp = std::move(src);
	m_Pos += sizeof(T);
	return *this;
}

template <typename T>
T* BufferWriter::Reserve(const uint32 count)
{
	if (FreeSize() < (sizeof(T)) * count)
		return nullptr;

	T* ret = reinterpret_cast<T*>(&m_Buffer[m_Pos]);
	m_Pos += sizeof(T) * count;
	return ret;
}
