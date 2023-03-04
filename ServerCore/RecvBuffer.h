#pragma once


/*---------------
	RecvBuffer
---------------*/

class RecvBuffer
{
	enum { BUFFER_COUNT = 10 };
public:
	RecvBuffer(uint32 bufferSize);
	~RecvBuffer();


	void			Clean();
	bool			OnWrite(uint32 numOfBytes);
	bool			OnRead(uint32 numOfBytes);

	BYTE*			ReadPos() { return &m_Buffer[m_ReadPos]; }
	BYTE*			WritePos() { return &m_Buffer[m_WritePos]; }
	uint32			DataSize() { return m_WritePos - m_ReadPos; }
	uint32			FreeSize() { return m_Capacity - m_WritePos; }

private:
	uint32			m_Capacity;
	uint32			m_BufferSize = 0;
	uint32			m_ReadPos = 0;
	uint32			m_WritePos = 0;
	Vector<BYTE>	m_Buffer;

};

