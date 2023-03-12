#pragma once
#include "BufferReader.h"
#include "BufferWriter.h"

enum
{
	// Client To Server
	CS_TEST = 1,


	// Server To Client
	SC_TEST = 10001,
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
	T* m_Data = nullptr;
	uint16	m_Count = 0;
};



class ServerPacketHandler
{
public:
	static void HandlePacket(BYTE* buffer, const uint32 len);

	static void Handle_CS_TEST(BYTE* buffer, const uint32 len);

	//static SendBufferRef Make_SC_TEST(const uint64 id, const uint32 hp, const uint16 attack, const vector<BuffData>& buffs, std::wstring name);
};

#pragma pack(1)
struct PKT_SC_TEST
{
	struct BuffListItem
	{
		uint64 buffId;
		float remainTime;

		uint16 victimOffset;
		uint16 victimCount;
	};

	uint16 packetSize;
	uint16 packetId;

	uint64 id;
	uint32 hp;
	uint16 attack;

	uint16 buffOffset;
	uint16 buffCount;

};


class PKT_SC_TEST_WRITE
{
public:
	using BuffListItem = PKT_SC_TEST::BuffListItem;
	using BuffList = PacketList<BuffListItem>;
	using BuffVictimList = PacketList<uint64>;

	PKT_SC_TEST_WRITE(const uint64 id, const uint32 hp, const uint16 attack)
	{
		m_SendBuffer = g_SendBufferManager->Open(4096);
		m_BufferWriter = BufferWriter(m_SendBuffer->Buffer(), m_SendBuffer->AllocSize());

		m_Pkt = m_BufferWriter.Reserve<PKT_SC_TEST>();
		m_Pkt->packetSize = 0;	// TO FILL
		m_Pkt->packetId = SC_TEST;
		m_Pkt->id = id;
		m_Pkt->hp = hp;
		m_Pkt->attack = attack;
		m_Pkt->buffOffset = 0;	// TO FILL
		m_Pkt->buffCount = 0;	// TO FILL
	}

	BuffList ReserveBuffList(const uint32 buffCount)
	{
		auto* firstBuffListItem = m_BufferWriter.Reserve<BuffListItem>(buffCount);
		m_Pkt->buffCount = buffCount;
		m_Pkt->buffOffset = reinterpret_cast<uint64>(firstBuffListItem) - reinterpret_cast<uint64>(m_Pkt);
		return BuffList(firstBuffListItem, buffCount);
	}

	BuffVictimList ReserveBuffVictimList(BuffListItem* buffItems, const uint32 victimCounts)
	{
		auto firstVictimListItem = m_BufferWriter.Reserve<uint64>(victimCounts);
		buffItems->victimOffset = reinterpret_cast<uint64>(firstVictimListItem) - reinterpret_cast<uint64>(m_Pkt);
		buffItems->victimCount = victimCounts;
		return BuffVictimList(firstVictimListItem, victimCounts);
	}

	SendBufferRef CloseAndReturn()
	{
		m_Pkt->packetSize = m_BufferWriter.WriteSize();
		m_SendBuffer->Close(m_BufferWriter.WriteSize());
		return m_SendBuffer;
	}

private:
	PKT_SC_TEST* m_Pkt = nullptr;
	SendBufferRef m_SendBuffer;
	BufferWriter m_BufferWriter;
};
#pragma pack()
