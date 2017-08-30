#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

//timeGetTime 함수를 사용하기 위한 라이브러리 추가
//윈도우가 시작되고 난 뒤의 시간을 리턴


timer::timer()
{
}


timer::~timer()
{
}

HRESULT timer::init()
{
	//고성능 타이머 지원여부를 치크한다.
	//고성능 타이머를 지원하면 초당 마이크로세컨드까지 값이 들어간다. (1/1000000)
	//시간 측정
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_periodFrequncy))
	{
		//64비트 정수를 사용할 수 있도록 정의한 이유는
		//마이크로 세컨드를(1/1000000)초 까지 측정하여 좀 더 정확한 시간값을 저장하기 위함)
		m_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_lastTime);

		//초당 시간 계싼 범위
		m_timeScale = 1.0f / m_periodFrequncy;
	}
	else
	{
		m_isHardware = false;
		//밀리세컨드 단위의 시간으로 초당 1000번 카운트
		m_lastTime = timeGetTime();
		m_timeScale = 0.001f;
	}

	m_frameRate = 0;
	m_FPSframeCount = 0;
	m_FPStimeElapsed = 0.0f;
	m_worldTime = 0;

	return S_OK;
}

void timer::tick(float lockFPS)
{
	//고성능 타이머를 지원한다면
	if (m_isHardware)
	{
		//초 정밀 마이크로초 단위로 계산
		QueryPerformanceCounter((LARGE_INTEGER*)&m_curTime);
	}
	else
	{
		//지원하지 않으면 time함수를 이용 밀리세컨드
		m_curTime = timeGetTime();
	}

	m_timeElapsed = (m_curTime - m_lastTime) * m_timeScale;

	if (lockFPS > 0.0f)
	{
		//고정 프레임 시간을 만족할 떄까지 루프시켜라
		while (m_timeElapsed < (1.0f / lockFPS))
		{
			if (m_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&m_curTime);
			else m_curTime = timeGetTime();

			//마지막 시간과 현재시간의 경과량
			m_timeElapsed = (m_curTime - m_lastTime) * m_timeScale;
		}
	}

	m_lastTime = m_curTime;				//마지막 시간을 기록
	m_FPSframeCount++;					//자동으로 프레임 카운트 증가
	m_FPStimeElapsed += m_timeElapsed;	//초당 프레임 시간 경과량 증가
	m_worldTime += m_timeElapsed;		//전체 시간 경과량 증가

	if (m_FPStimeElapsed > 1.0f)
	{
		m_frameRate = m_FPSframeCount;
		m_FPSframeCount = 0;
		m_FPStimeElapsed = 0.0f;
	}
}

unsigned long timer::getFrameRate(char * str) const
{
	if (str != nullptr)
	{
		wsprintf(str, "FPS: %d", m_frameRate);
	}

	return m_frameRate;
}
