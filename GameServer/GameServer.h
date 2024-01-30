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
	static ptr<GameServer> Instance()
	{
		static ptr<GameServer> gameServer = MakeShared<GameServer>();
		return gameServer;
	}

	void InitChannel();
	bool Init();
	void Run();
	void Shutdown();

	const ServerOptionData& GetServerOption() const { return m_ServerOption; }

	bool IsRunning() { return m_ServerStartFlag; }
	bool IsClosing() { return m_ServerClosingFlag; }

	void IncreaseRunningThreadCounts() {  m_WorkerRunningCounts.fetch_add(1); }

	static uint32 RebootChannel(uint32 channelKey);
	static void CloseChennel(uint32 channelKey);


private:
	GameServer() = default;

	static uint32 CreateChannel();

	bool InitConfigParser();
	bool InitScriptParser();
	bool InitServerService();
	void InitWorkerThread();
	bool Update(uint64 deltaTick);




	// for party system 채널이 달라도 파티는 가능함...
	HashMap<uint32, shared_ptr<Room>> m_RoomMaps;

	//
	ServerOptionData m_ServerOption;

	shared_ptr<UpdateTickControl> m_UpdateControl;

	//KeyboardInputCapture m_ServerInputControl;

	atomic<uint32> m_WorkerRunningCounts = 0;

	HashSet<uint32> m_ChannelKeySet;
	ServerServicePtr	m_Service;

	volatile bool m_ServerStartFlag = false;
	volatile bool m_ServerClosingFlag = false;
};
