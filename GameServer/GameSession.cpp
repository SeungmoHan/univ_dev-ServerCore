#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"
#include "Room.h"
#include "Player.h"

void	GameSession::OnConnect()
{
	GameSessionManager::Instance()->Add(static_pointer_cast<GameSession>(shared_from_this()));
};

void	GameSession::OnRecvPacket(BYTE* buffer, const int32 len)
{
	auto session = GetPacketSessionPtr();
	auto header = reinterpret_cast<PacketHeader*>(buffer);

	//TODO PacketID 대역 체크
	ClientPacketHandler::HandlePacket(session, buffer, len);
}

void	GameSession::OnSend(int32 len)
{

};

void	GameSession::OnDisconnected() 
{
	GameSessionManager::Instance()->Remove(static_pointer_cast<GameSession>(shared_from_this()));

	// 나갈때 현재 사용중인 플레이어가 있으면
	if(m_CurrentPlayer)
	{
		// 방이 있으면
		if(const auto room = m_CurrentPlayer->GetCurrentRoom())
		{
			// 방탈출 잡 실행
			if (room != nullptr)
				room->DoAsync(&Room::Leave, m_CurrentPlayer);
		}
	}
	m_CurrentPlayer = nullptr;
	m_Players.clear();

}

void GameSession::AddPlayer(PlayerPtr newPlayer)
{
	m_Players.push_back(newPlayer);
}

void GameSession::SetSelectedPlayer(const size_t playerIndex)
{
	if (is_valid(playerIndex))
		m_CurrentPlayer = m_Players[playerIndex];
}

PlayerPtr GameSession::GetPlayer(size_t playerIndex)
{
	if (is_valid(playerIndex))
		return m_Players[playerIndex];
	return nullptr;
}

bool GameSession::is_valid(const size_t index) const
{
	return index < m_Players.size();
};
