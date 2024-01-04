#pragma once

#include "Session.h"

class GameSession : public PacketSession
{
	DECLARE_TL(SessionTL);
public:
	virtual ~GameSession()
	{
		cout << "~GameSession" << endl;
	}
	virtual void	OnConnect() override;
	//virtual int32	OnRecv(BYTE* buffer, int32 len) override;
	virtual void	OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void	OnSend(int32 len) override;
	virtual void	OnDisconnected() override;

public:
	void AddPlayer(PlayerPtr newPlayer);

	PlayerPtr GetSelectedPlayer() const { return m_CurrentPlayer; }
	void SetSelectedPlayer(const size_t playerIndex);

	PlayerPtr GetPlayer(size_t playerIndex);

private:
	bool is_valid(const size_t index) const;


	Vector<PlayerPtr> m_Players = {};
	PlayerPtr m_CurrentPlayer = nullptr;
};

