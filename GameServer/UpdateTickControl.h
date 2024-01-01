#pragma once

class UpdateTickControl
{
public:
	explicit UpdateTickControl() = default;

	bool Update();

	uint64 GetDeltaTick() const
	{
		return m_LastTick - m_CurTick;
	}
	~UpdateTickControl() = default;

private:
	uint64	m_LastTick = 0;
	uint64	m_CurTick = 0;
	uint64	m_DeltaTick = 0;
};
