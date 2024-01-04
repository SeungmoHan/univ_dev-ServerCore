#include "pch.h"
#include "GameSessionManager.h"
#include "GameSession.h"



void GameSessionManager::Add(GameSessionPtr session)
{
	WRITE_LOCK;
	m_Sessions.emplace(session);
}

void GameSessionManager::Remove(const GameSessionPtr session)
{
	WRITE_LOCK;
	m_Sessions.erase(session);
}

void GameSessionManager::Broadcast(const SendBufferPtr sendBuffer)
{
	READ_LOCK;
	for (const GameSessionPtr session : m_Sessions)
	{
		session->Send(sendBuffer);
	}
}

bool GameSessionManager::Update(uint64 deltaTick)
{
	for(GameSessionPtr session : this->m_Sessions)
	{
		if (session->IsConnected() == false)
		{
			session->Disconnect(L"Not Connected Update");
			continue;
		}

		PlayerPtr curPlayer = session->GetSelectedPlayer();
		//if (curPlayer->Update() == false)
		//{
		//	continue;
		//}
	}
	return true;
}

void GameSessionManager::RemoveAll()
{
	for(GameSessionPtr session : m_Sessions)
	{
		session->Disconnect(L"Remove all Connection");
	}
}
