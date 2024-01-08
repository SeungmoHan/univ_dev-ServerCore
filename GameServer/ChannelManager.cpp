#include "pch.h"
#include "Protocol.pb.h"
#include "Channel.h"
#include "ChannelManager.h"
#include "GameServer.h"
#include "Player.h"
#include "ThreadManager.h"

ChannelManager& ChannelManager::Instance()
{
	static ChannelManager instance;
	return instance;
}

uint32 ChannelManager::AttatchChannel()
{
	const auto channelKey = m_ChannelKey.top();
	// ChannelKey 의 최소값은 1이다...
	if(m_ChannelMap.find(channelKey) != m_ChannelMap.end())
		return 0;
	m_ChannelKey.pop();
	const auto newChannel = MakeShared<Channel>();

	const auto channelName = L"Channel_" + std::to_wstring(channelKey);
	const auto maxSessionCounts = GameServer::Instance()->GetServerOption().m_MaxPlayerPerChannel;
	const Channel::ChannelOption newOption{ channelKey, channelName, maxSessionCounts, 0 };

	g_ThreadManager->Launch(
		[=]()
		{
			newChannel->Init(newOption, GameServer::Instance());
			newChannel->Run();
			newChannel->Clear();
		});

	return channelKey;
}

bool ChannelManager::DetatchChannel(uint32 channelId)
{
	const auto channel = GetChannel(channelId);
	if (channel == nullptr)
		return false;
	channel->Close();
	m_ChannelKey.push(channelId);
	m_ChannelMap.erase(channelId);
	return true;
}

void ChannelManager::MoveChannel(const uint32 from, const uint32 to, const PlayerPtr player)
{
	if(const auto fromChannel = GetChannel(from); fromChannel != nullptr)
	{
		fromChannel->DoAsync<Channel, void>(&Channel::MoveChannel, to, player);
	}
}

void ChannelManager::GetChannelIDs(OUT vector<uint32>& ids)
{
	for (auto [key, channel] : m_ChannelMap)
		ids.push_back(key);
}

ptr<Channel> ChannelManager::GetChannel(const uint32 channelId)
{
	const auto itr = m_ChannelMap.find(channelId);
	if (itr == m_ChannelMap.end())
		return nullptr;
	return itr->second;
}




ChannelManager::ChannelManager() 
{
	for(int i=1; i <= MaxChannelCounts; i++)
		m_ChannelKey.emplace(i);
	// Do nothing...

}
