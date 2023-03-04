#pragma once


class GameSession;


using GameSessionRef = shared_ptr<GameSession>;

class GameSessionManager
{
public:
	void Add(GameSessionRef session);
	void Remove(GameSessionRef session);
	void Broadcast(SendBufferRef sendBuffer);

	static GameSessionManager* Instance()
	{
		static GameSessionManager* manager = new GameSessionManager();
		return manager;
	}
private:
	USE_LOCK;

	Set<GameSessionRef> m_Sessions;
};