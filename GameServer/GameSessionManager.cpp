#include "pch.h"
#include "GameSessionManager.h"
#include "GameSession.h"



void GameSessionManager::Add(GameSessionRef session)
{
	WRITE_LOCK;
	m_Sessions.emplace(session);
}

void GameSessionManager::Remove(const GameSessionRef session)
{
	WRITE_LOCK;
	m_Sessions.erase(session);
}

void GameSessionManager::Broadcast(const SendBufferRef sendBuffer)
{
	WRITE_LOCK;
	for (const GameSessionRef session : m_Sessions)
	{
		session->Send(sendBuffer);
	}
}
