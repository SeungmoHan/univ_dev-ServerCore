#pragma once

class ServerOptionData
{
public:
	enum eServerMode
	{
		NONE = 0, DEV, RELEASE, LIVE,
	};

	static eServerMode StringToMode(const wstring& mode)
	{
		static unordered_map<wstring, eServerMode> m;
		if(m.empty())
		{
			m.emplace(L"DEV", DEV);
			m.emplace(L"RELEASE", RELEASE);
			m.emplace(L"LIVE", LIVE);
		}
		if (m.find(mode) == m.end())
			return NONE;
		return m[mode];
	}
	// 일단은 필요한건 이정도다 추가로 필요한건 개발하면서 넣자.


	eServerMode		m_Mode = NONE;
	wstring			m_DataScriptPath;
	wstring			m_LogPath;
	wstring			m_IP;
	uint16			m_Port = {};
	uint32			m_MaxSessionCounts = {};
	uint32			m_ServerFPS = {};
	uint32			m_WorkerThreadCounts = 0;
	uint32			m_ChannelCounts = 0;
	uint32			m_MaxPlayerPerChannel = 0;
	uint32			m_MaxCharacterPerPlayer = 0;
	uint32			m_MaxSectorSize = 0;
};
