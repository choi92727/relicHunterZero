#include "stdafx.h"
#include "timeManager.h"


timeManager::timeManager()
{
}


timeManager::~timeManager()
{
}

HRESULT timeManager::init()
{
	m_timer = new timer;
	m_timer->init();
	return S_OK;
}

void timeManager::release()
{
	if (m_timer != nullptr)
	{
		SAFE_DELETE(m_timer);
		m_timer = nullptr;
	}
}

void timeManager::update(float lock)
{
	if (m_timer != nullptr)
	{
		m_timer->tick(lock);
	}
}

void timeManager::render(HDC hdc)
{
	char str[256];
	string strFrame;
	//글자 배경모드
	SetBkMode(hdc, TRANSPARENT);
	//글자 색상
	SetTextColor(hdc, RGB(0, 0, 255));

#ifdef _DEBUG
	if (m_timer != nullptr)
	{
		//FPS
		sprintf(str, "FPS: %d", m_timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		//전체경과시간
		sprintf(str, "worldTime: %f", m_timer->getWorldTime()); //L"내용" 유니코드
		TextOut(hdc, 0, 20, str, strlen(str)); //wcslen()

											   //한프레임당 경과시간
		sprintf(str, "ElapsedTime: %f", m_timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));
	}
#else
	if (m_timer != nullptr)
	{
		//FPS
		wsprintf(str, "FPS: %d", m_timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif
}
