#include "stdafx.h"
#include "pixelCollisionScene.h"

pixelCollisionScene::pixelCollisionScene()
{
}

pixelCollisionScene::~pixelCollisionScene()
{
}

HRESULT pixelCollisionScene::init()
{
	IMAGEMANAGER->addImage("산", "images/mountain.bmp", 800, 600, true, RGB(255, 0, 255));

	m_ball = IMAGEMANAGER->addImage("ball", "images/ball.bmp", 60, 60, true, RGB(255, 0, 255));

	m_x = WINSIZEX / 2 - 100;
	m_y = WINSIZEY / 2 + 100;
	m_rc = RectMakeCenter(m_x, m_y, m_ball->getWidth(), m_ball->getHeight());

	//y축으로 탐지할 사각형
	m_probeY = m_y + m_ball->getHeight() / 2;

	return S_OK;
}

void pixelCollisionScene::release()
{
}

void pixelCollisionScene::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_x -= 2.0f;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_x += 2.0f;
	}

	//탐지할 y값 지속적으로 업데이트
	m_probeY = m_y + m_ball->getHeight() / 2;

	//탐지할 y값 범위를 위아래로 원하는만큼 검사
	for (int i = m_probeY - 10; i < m_probeY + 10; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("산")->getMemDC(), m_x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//이 조건만 본인들이 원하는 픽셀충돌 픽셀값으로 설정
		if (!(r == 255 && g == 0 && b == 255))
		{
			m_y = i- m_ball->getHeight() / 2;
			break;
		}
	}
	m_rc = RectMakeCenter(m_x, m_y, m_ball->getWidth(), m_ball->getHeight());

}

void pixelCollisionScene::render()
{
	IMAGEMANAGER->findImage("산")->render(getMemDC());

	m_ball->render(getMemDC(), m_rc.left, m_rc.top);

	//감지할 사각형
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		Rectangle(getMemDC(), m_x, m_probeY, m_x + 10, m_probeY + 10);
	}
}
