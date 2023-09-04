#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"
#include "Room.h"

void	GameSession::OnConnect() 
{
	GameSessionManager::Instance()->Add(static_pointer_cast<GameSession>(shared_from_this()));
};

void	GameSession::OnRecvPacket(BYTE* buffer, const int32 len)
{
	auto session = GetPacketSessionRef();
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
		if(const auto room = m_Room.lock())
		{
			// ��Ż�� �� ����
			room->DoAsync(&Room::Leave, m_CurrentPlayer);
		}
	}
	m_CurrentPlayer = nullptr;
	m_Players.clear();

};