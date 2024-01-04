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

	//TODO PacketID �뿪 üũ
	ClientPacketHandler::HandlePacket(session, buffer, len);
}

void	GameSession::OnSend(int32 len)
{

};

void	GameSession::OnDisconnected() 
{
	GameSessionManager::Instance()->Remove(static_pointer_cast<GameSession>(shared_from_this()));

	// ������ ���� ������� �÷��̾ ������
	if(m_CurrentPlayer)
	{
		// ���� ������
		if(const auto room = m_CurrentPlayer->GetCurrentRoom())
		{
			// ��Ż�� �� ����
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
