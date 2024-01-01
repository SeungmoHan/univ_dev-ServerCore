#pragma once
#include "ServerOptions.h"

class Room;
class ConfigParser;
class GameScriptParser;

class GameServer
{
public:
	static GameServer& Instance()
	{
		static GameServer gameServer;
		return gameServer;
	}
	bool Init();
	void Run();

private:
	GameServer() = default;

	bool InitConfigParser();
	bool InitScriptParser();
	bool InitServerService();
	void InitWorkerThread();
	bool Update(uint64 deltaTick);


	bool CheckUpdate(uint64& OUT deltaTick);


	shared_ptr<GameScriptParser>	m_ScriptParser = nullptr;

	ServerServicePtr	m_Service;

	shared_ptr<Room> m_LobbyRoom;
	HashMap<uint32, shared_ptr<Room>> m_RoomMaps;

	//
	ServerOptionData m_ServerOption;

	volatile bool m_ServerRunningFlag = false;
};
