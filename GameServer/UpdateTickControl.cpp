#include "pch.h"
#include "GameServer.h"
#include "UpdateTickControl.h"

#include "Channel.h"

UpdateTickControl::UpdateTickControl(const uint32 desiredFrame) : m_DesiredFPS(desiredFrame)
{
	
}
thread_local bool frameSkipFlag;
thread_local int cur = timeGetTime();
thread_local int old = timeGetTime();
thread_local int deltaTime;
thread_local int skipTime = 0;


// true == 게임서버 업데이트o, false == 게임서버 업데이트x
void UpdateTickControl::Update()
{
	// log 관련한거
	{
		// 1초에 몇번 호출 했는지 확인하려고...
		m_LogTotalFrame++;
		if (m_CurTick >= m_LogLastTick + SECOND)
		{
			const auto fps = m_LogTotalFrame - m_LogLastFrame;
			m_LogLastFrame = m_LogTotalFrame;
			m_LogLastTick = m_CurTick;
            cout << fps << endl;
		}
	}

    const int32 desiredSpendTime = 1000 / m_DesiredFPS;
    m_CurTick = timeGetTime();
    if (m_FrameSkipFlag)
    {
        m_LastTick = m_CurTick - (m_DeltaTick - (desiredSpendTime - (m_CurTick - m_SkippedTime)));
        m_FrameSkipFlag = false;
    }
    m_DeltaTick = m_CurTick - m_LastTick;

    if (m_DeltaTick >= desiredSpendTime*2 == false)
    {
        if (m_DeltaTick < desiredSpendTime)
        {
            m_SleepTime_ms = desiredSpendTime - m_DeltaTick;
            DelayFrame();
        }
        m_LastTick = m_CurTick - (m_DeltaTick - desiredSpendTime);
    }
    else
    {
        m_FrameSkipFlag = true;
        m_SkippedTime = m_CurTick;
    }
}

void UpdateTickControl::DelayFrame()
{
	if (m_SleepTime_ms > 0)
	{
		const chrono::milliseconds sleepTime(m_SleepTime_ms);
		this_thread::sleep_for(sleepTime);
		m_SleepTime_ms = 0;
	}
}
