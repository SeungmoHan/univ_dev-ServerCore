#pragma once
#include "ServerOptions.h"

class UpdateTickControl;
class Room;
class ConfigParser;
class GameScriptParser;

class GameServer
{
	// memory alloc 관련 singleton 만들려고하는데
	// 생성자에서 호출하는 xnew, xdelete MakeShared가 문제가 되었음 ㅠ
	template<typename Type, typename...Args>
	friend Type* xnew(Args&&... args);
	template<typename Type>
	friend void xdelete(Type* ptr);
	template<typename Type, typename... Args>
	friend shared_ptr<Type> MakeShared(Args&&...args);


public:
	static GameServer& Instance()
	{
		static GameServer gameServer;
		return gameServer;
	}
	bool Init();
	void Run();
	void Shutdown();

	const ServerOptionData& GetServerOption() const { return m_ServerOption; }

	bool IsRunning() { return m_ServerStartFlag; }
	bool IsClosing() { return m_ServerClosingFlag; }

	void IncreaseRunningThreadCounts() {  m_WorkerRunningCounts.fetch_add(1); }

private:
	GameServer() = default;

	bool InitConfigParser();
	bool InitScriptParser();
	bool InitServerService();
	void InitWorkerThread();
	bool Update(uint64 deltaTick);


	shared_ptr<GameScriptParser>	m_ScriptParser = nullptr;

	ServerServicePtr	m_Service;

	shared_ptr<Room> m_LobbyRoom;
	HashMap<uint32, shared_ptr<Room>> m_RoomMaps;

	//
	ServerOptionData m_ServerOption;

	shared_ptr<UpdateTickControl> m_UpdateControl;

	//KeyboardInputCapture m_ServerInputControl;

	atomic<uint32> m_WorkerRunningCounts = 0;

	volatile bool m_ServerStartFlag = false;
	volatile bool m_ServerClosingFlag = false;
};
