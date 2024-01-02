#pragma once


class GameServer;

class UpdateTickControl
{
public:
	constexpr static uint64 SECOND = 1000;
	explicit UpdateTickControl(GameServer& ownerServer, uint32 desiredFPS);\
	bool Update();

	uint64 GetDeltaTick() const
	{
		return m_LastTick - m_CurTick;
	}
	~UpdateTickControl() = default;
	void DelayFrame();

private:

	// 프레임 타임 관련 변수들
	uint64	m_LastTick = GetTickCount64();
	uint64	m_CurTick = GetTickCount64();
	uint32	m_DesiredFPS;


	uint64 m_SleepTime_ms = 0;

	// 초당 프레임 수
	uint32 m_LogTotalFrame = 0;
	uint32 m_LogLastFrame = 0;
	uint64 m_LogLastTick = 0;
};
