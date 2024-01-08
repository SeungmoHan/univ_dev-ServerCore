#pragma once

class ChannelManager
{
public:
	enum 
	{
		MaxChannelCounts = 50,
	};
	static ChannelManager& Instance();

	// fail for 0
	uint32 AttatchChannel();
	bool DetatchChannel(uint32 channelId);

	void MoveChannel(uint32 from, uint32 to, PlayerPtr player);


	void GetChannelIDs(vector<uint32>& OUT ids);
	ptr<Channel> GetChannel(uint32 channelId);

private:
	ChannelManager();
	priority_queue<uint32, vector<uint32>,greater<>> m_ChannelKey;
	HashMap<uint32, ChannelPtr> m_ChannelMap;
};
