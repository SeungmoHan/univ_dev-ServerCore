#pragma once


class SendBufferChunk;
/*------------------
	 SendBuffer
------------------*/

class SendBuffer : public enable_shared_from_this<SendBuffer>
{

public:
	SendBuffer(SendBufferChunkRef owner, BYTE* buffer, uint32 bufferSize);
	~SendBuffer();

	BYTE*		Buffer() { return m_Buffer; }
	uint32		WriteSize() const { return m_WriteSize; }
	void		Close(uint32 writeSize);
private:
	BYTE* m_Buffer;

	uint32				m_AllocSize = 0;
	uint32				m_WriteSize = 0;

	SendBufferChunkRef	m_Owner;
};

/*----------------------
	 SendBufferChunk
----------------------*/
class SendBufferChunk : public enable_shared_from_this<SendBufferChunk>
{
private:
	enum 
	{
		SEND_BUFFER_CHUNK_SIZE = 0x10000,
	};

public:
	SendBufferChunk();
	~SendBufferChunk();

	void			Reset();
	SendBufferRef	Open(uint32 allocSize);
	void			Close(uint32 writeSize);

	bool			IsOpen() { return m_Open; };
	BYTE*			Buffer() { return &m_Buffer[m_UsedSize]; }
	uint32			FreeSize() { return static_cast<uint32>(m_Buffer.size()) - m_UsedSize; }

private:
	Array<BYTE, SEND_BUFFER_CHUNK_SIZE> m_Buffer = {};
	bool								m_Open = false;
	uint32								m_UsedSize = 0;

};


/*------------------------
	 SendBufferManager
------------------------*/
class SendBufferManager
{
public:
	SendBufferRef Open(uint32 size);

private:
	SendBufferChunkRef	Pop();
	void				Push(SendBufferChunkRef buffer);

	static void			PushGlobal(SendBufferChunk* buffer);

private:
	USE_LOCK;
	Vector<SendBufferChunkRef> m_SendBufferChunks;

};