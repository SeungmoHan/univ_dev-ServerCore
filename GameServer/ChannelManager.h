#pragma once

class ChannelManager
{
public:
	enum 
	{
		MaxChannelCounts = 50,
	};
	static ChannelManager& Instance();
	ChannelPtr DefaultChannel() { return m_ChannelMap[DefaultChannelID()]; }
	uint32 DefaultChannelID() { return 0; }

	// fail for 0
	uint32 AttatchChannel();
	bool DetatchChannel(uint32 channelId);

	void MoveChannel(uint32 from, uint32 to, PlayerPtr player);


	void GetChannelIDs(vector<uint32>& OUT ids);
	ptr<Channel> GetChannel(uint32 channelId);

private:
	ChannelManager();

	//채널 생성과 삭제는 GameServer 메인 쓰레드에 의해서만 작동한다 락은 필요없다.
	//다만 유저가 입장과 퇴장할 때 채널 리스트를 보내줘야해서
	//참조할 수 있는데 그 때 하필 삭제될 수도있음...
	priority_queue<uint32, vector<uint32>,greater<>> m_ChannelKey;
	HashMap<uint32, ChannelPtr> m_ChannelMap;
	USE_LOCK;
};
