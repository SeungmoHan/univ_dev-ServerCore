#include "pch.h"
#include "GameServer.h"
#include "UpdateTickControl.h"


UpdateTickControl::UpdateTickControl(GameServer& ownerServer, uint32 desiredFPS): m_DesiredFPS(ownerServer.GetServerOption().m_ServerFPS)
{
}

// true == 게임서버 업데이트o, false == 게임서버 업데이트x
bool UpdateTickControl::Update()
{
	const uint64 desiredSpendTime = 1000 / m_DesiredFPS;
	// 1. 업데이트 틱에대한 업데이트
	m_CurTick = GetTickCount64();

	// 2. 1에서 나온 정보를 가지고 게임서버의 업데이트를 할지 말지를 처리할거임.
	if(m_CurTick - m_LastTick < desiredSpendTime)
	{
		// 아직 다음번 틱이 안된거임
		return false;
	}
	// 현재 시간이 이전시간 + 소모희망시간 보다 더 길면... sleep 시간을 줄여야함
	// 현재 시간이 이전시간 + 소모희망시간 보다 더 짧으면... 그만큼 sleep 해줘야함
	// 3. 마지막 프레임 틱 업데이트
	m_LastTick += desiredSpendTime;
	const uint64 sleepTime = m_LastTick - m_CurTick;
	constexpr uint64 Zero = 0;
	m_SleepTime_ms = max(sleepTime, Zero);
	// log 관련한거
	{
		// 1초에 몇번 호출 했는지 확인하려고...
		m_LogTotalFrame++;
		if(m_CurTick >= m_LogLastTick + SECOND)
		{
			auto fps = m_LogTotalFrame - m_LogLastFrame;
			cout << "FPS : " << fps << endl;
			m_LogLastFrame = m_LogTotalFrame;
			m_LogLastTick = m_CurTick;
		}
	}
	return true;
}

void UpdateTickControl::DelayFrame()
{
	if (m_SleepTime_ms > 0)
	{
		chrono::milliseconds sleepTime(m_SleepTime_ms);
		this_thread::sleep_for(sleepTime);
	}
}
