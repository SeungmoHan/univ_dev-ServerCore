#pragma once


class GameServer;

class UpdateTickControl
{
public:
	constexpr static int32 SECOND = 1000;
	explicit UpdateTickControl(uint32 desiredFrame);
	void Update();

	int32 GetDeltaTick() const
	{
		return m_DeltaTick;
	}
	~UpdateTickControl() = default;
	void DelayFrame();
	uint32 GetServerFrame() const { return m_LogTotalFrame; }

private:

	// 프레임 타임 관련 변수들
	int32	m_LastTick = timeGetTime();
	int32	m_CurTick = timeGetTime();
	int32	m_SkippedTime = 0;
	int32	m_DeltaTick = 0;
	bool	m_FrameSkipFlag = false;

	int32	m_SleepTime_ms = 0;
	uint32	m_DesiredFPS = 0;




	// 초당 프레임 수
	uint64 m_LogTotalFrame = 0;
	uint64 m_LogLastFrame = 0;
	int32 m_LogLastTick = 0;
};

