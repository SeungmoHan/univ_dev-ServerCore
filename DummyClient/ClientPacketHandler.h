#pragma once

enum
{
	// Client To Server
	CS_TEST = 1,


	// Server To Client
	SC_TEST = 10001,
};


class ClientPacketHandler
{
public:

	static void HandlePacket(BYTE* buffer, const uint32 len);

	static void Handle_SC_TEST(BYTE* buffer, const uint32 len);
};


template<typename T, typename C>
class PacketIterator
{
public:
	PacketIterator(C& container, const uint32 index) : m_Container(container), m_Index(index) {};

	bool operator !=(const PacketIterator& other) const { return other.m_Index != m_Index; }
	const T& operator*() const { return m_Container[m_Index]; }
	T& operator*() { return m_Container[m_Index]; }
	T* operator->() { return &m_Container[m_Index]; }
	PacketIterator& operator++() { m_Index++; return *this; }
	PacketIterator operator++(int32) { PacketIterator ret = *this; m_Index++; return ret; }

private:
	C& m_Container;
	uint32 m_Index;
};

template <typename T>
class PacketList
{
public:
	PacketList() : m_Data(nullptr), m_Count(0) {};
	PacketList(T* data, const uint16 count) : m_Data(data), m_Count(count) {}

	T& operator[](const uint32 index)
	{
		ASSERT_CRASH(index < m_Count);
		return m_Data[index];
	}
	uint32 GetCount() const { return m_Count; }

	PacketIterator<T, PacketList<T>> begin() { return PacketIterator<T, PacketList<T>>(*this, 0); }
	PacketIterator<T, PacketList<T>> end() { return PacketIterator<T, PacketList<T>>(*this, m_Count); }
private:
	T*		m_Data		= nullptr;
	uint16	m_Count		= 0;
};

#pragma pack(1)
struct PKT_SC_TEST
{
	struct BuffListItem
	{
		uint64 buffId;
		float remainTime;

		uint16 victimeOffset;
		uint16 victimCount;

		bool Validate(BYTE* packetStart, uint16 packetSize, OUT uint32& size) const
		{
			if (victimeOffset + victimCount * sizeof(uint64) > packetSize)
				return false;

			size += victimCount * sizeof(uint64);
			return true;
		}
	};


	uint16 packetSize;
	uint16 packetId;

	uint64 id;
	uint32 hp;
	uint16 attack;

	uint16 buffOffset;
	uint16 buffCount;

	bool Validate() 
	{
		uint32 size = 0;
		size += sizeof(PKT_SC_TEST);
		if (packetSize < size)
			return false;

		if (buffOffset + buffCount * sizeof(BuffListItem) > packetSize)
			return false;

		size += buffCount * sizeof(BuffListItem);

		BuffList buffList = GetBuffList();
		for(uint32 i =0; i< buffList.GetCount(); i++)
		{
			if (false == buffList[i].Validate(reinterpret_cast<BYTE*>(this), packetSize, OUT size))
				return false;
		}

		if (size != packetSize)
			return false;

		return true;
	}
	using BuffList = PacketList<BuffListItem>;
	using BuffVictimList = PacketList<uint64>;

	BuffList GetBuffList()
	{
		auto data = reinterpret_cast<BYTE*>(this);
		data += buffOffset;
		return BuffList(reinterpret_cast<BuffListItem*>(data), buffCount);
	}

	BuffVictimList GetBuffVictimList(const BuffListItem* buffItem)
	{
		auto data = reinterpret_cast<BYTE*>(this);
		data += buffItem->victimeOffset;
		return BuffVictimList(reinterpret_cast<uint64*>(data), buffItem->victimCount);
	}
};
#pragma pack()