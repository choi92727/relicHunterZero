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
	//���� �����
	SetBkMode(hdc, TRANSPARENT);
	//���� ����
	SetTextColor(hdc, RGB(0, 0, 255));

#ifdef _DEBUG
	if (m_timer != nullptr)
	{
		//FPS
		sprintf(str, "FPS: %d", m_timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));

		//��ü����ð�
		sprintf(str, "worldTime: %f", m_timer->getWorldTime()); //L"����" �����ڵ�
		TextOut(hdc, 0, 20, str, strlen(str)); //wcslen()

											   //�������Ӵ� ����ð�
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
