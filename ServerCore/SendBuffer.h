#pragma once


class SendBufferChunk;
/*------------------
	 SendBuffer
------------------*/

class SendBuffer : public enable_shared_from_this<SendBuffer>
{

public:
	SendBuffer(SendBufferChunkPtr owner, BYTE* buffer, uint32 bufferSize);
	~SendBuffer();

	BYTE*		Buffer() const;

	uint32		AllocSize() const;

	uint32		WriteSize() const;
	void		Close(uint32 writeSize);
private:
	BYTE* m_Buffer;

	uint32				m_AllocSize = 0;
	uint32				m_WriteSize = 0;

	SendBufferChunkPtr	m_Owner;
};

/*----------------------
	 SendBufferChunk
----------------------*/
class SendBufferChunk : public enable_shared_from_this<SendBufferChunk>
{
private:
	enum 
	{
		SEND_BUFFER_CHUNK_SIZE = 4444,
	};

public:
	SendBufferChunk();
	~SendBufferChunk();

	void			Reset();
	SendBufferPtr	Open(uint32 allocSize);
	void			Close(uint32 writeSize);

	bool			IsOpen() const;;
	BYTE*			Buffer();
	uint32			FreeSize() const;

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
	SendBufferPtr Open(uint32 size);

private:
	SendBufferChunkPtr	Pop();
	void				Push(SendBufferChunkPtr buffer);

	static void			PushGlobal(SendBufferChunk* buffer);

private:
	USE_LOCK;
	Vector<SendBufferChunkPtr> m_SendBufferChunks;

};