#pragma once


class GameSession;


using GameSessionPtr = shared_ptr<GameSession>;

class GameSessionManager
{
public:
	void Add(GameSessionPtr session);
	void Remove(GameSessionPtr session);
	void Broadcast(SendBufferPtr sendBuffer);

	static GameSessionManager* Instance()
	{
		static GameSessionManager* manager = new GameSessionManager();
		return manager;
	}

	bool Update(uint64 deltaTick);

	void RemoveAll();
private:
	USE_LOCK;

	Set<GameSessionPtr> m_Sessions;
};