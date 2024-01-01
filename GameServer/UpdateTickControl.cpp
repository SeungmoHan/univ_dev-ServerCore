#include "pch.h"
#include "UpdateTickControl.h"

bool UpdateTickControl::Update()
{
	// 1. 업데이트 틱에대한 업데이트
	m_DeltaTick = m_LastTick - m_CurTick;


	// 2. 1에서 나온 정보를 가지고 게임서버의 업데이트를 할지 말지를 처리할거임.



	m_LastTick = m_CurTick;

	return true;
}
