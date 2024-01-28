#pragma once
#include "JobSerializer.h"

class GameServer;
class UpdateTickControl;
class Field;
class Room;

class Channel : public JobSerializer
{
public:
	~Channel() override = default;

	struct ChannelOption
	{
		uint32 _channelKey = 0;
		wstring _channelName;
		uint32 _maxPlayerCounts = 0;
		uint32 _curPlayerCounts = 0;
	};
	PlayerPtr GetPlayer(uint64 playerId);

	const ChannelOption& GetChannelOption() const { return m_ChannelOption; }

	void Init(const ChannelOption& channelOption, const ptr<GameServer>& owner);
	void Run();
	void Clear();

	void MoveChannel(const uint32 toKey, PlayerPtr player);
	void MoveChannel(const uint32 toKey, const uint64 playerKey);
	void RemovePlayer(const uint64 playerKey);
	void AddPlayer(PlayerPtr player);
	void Close();

	void RemoveAllPlayer();

	void EnterField(const uint64 fieldCode, PlayerPtr player);
	uint64 GetStartFieldCode();

	virtual bool CanEnter() const;
	virtual bool Update(uint64 deltaTick);
private:

	ChannelOption m_ChannelOption;

	ptr<Field> m_StartField = nullptr;
	HashMap<uint64, ptr<Field>> m_FieldMap;
	HashMap<uint64, ptr<Room>> m_RoomMap;
	HashMap<uint64, PlayerPtr> m_PlayerMap;

	ptr<UpdateTickControl> m_UpdateControl;

	volatile bool m_ChannelStartFlag = false;
	volatile bool m_ChannelCloseFlag = false;

	ptr<GameServer> m_OwnerServer;

};


using ChannelPtr = ptr<Channel>;