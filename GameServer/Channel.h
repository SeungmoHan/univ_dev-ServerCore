#pragma once
#include "JobSerializer.h"

class GameServer;
class UpdateTickControl;

class Channel : public JobSerializer
{
public:
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
	void RemovePlayer(PlayerPtr player);
	void AddPlayer(PlayerPtr player);
	void Close();

	void RemoveAllPlayer();

	bool CanEnter() const;

private:
	bool Update(uint64 deltaTick);




	ChannelOption m_ChannelOption;

	HashMap<uint64, PlayerPtr> m_PlayerMap;

	ptr<UpdateTickControl> m_UpdateControl;

	volatile bool m_ChannelStartFlag = false;
	volatile bool m_ChannelCloseFlag = false;

	ptr<GameServer> m_OwnerServer;

};


using ChannelPtr = ptr<Channel>;