#pragma once

class Player
{
public:
	uint64					m_PlayerId = 0;
	string					m_Name;
	Protocol::PlayerType	m_Type = Protocol::PLAYER_TYPE_NONE;
	GameSessionPtr			m_OwnerSession;
};

