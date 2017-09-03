#include "stdafx.h"
#include "defaultGun.h"


defaultGun::defaultGun()
{
}


defaultGun::~defaultGun()
{
}

HRESULT defaultGun::init(int x, int y)
{
	m_x = x;
	m_y = y;
	m_defaultGunImage = new Image(L"images/spr_pistol_jimmy_0.png");
	m_graphics = new Graphics(getMemDC());
	angle = 0;
	m_defaultBullet = new defaultBullet;
	m_defaultBullet->init();
	return S_OK;
}



void defaultGun::release()
{
}

void defaultGun::update()
{


	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		addAngle -= 1 * (PI / 180);
	}
	
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		addAngle += 1 * (PI / 180);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		m_defaultBullet->fire(m_x, m_y, angle, 10);
	}

	angle = getAngle(m_x +  IMAGEMANAGER->findImage("±ÇÃÑ")->getWidth()/2
		,m_y + IMAGEMANAGER->findImage("±ÇÃÑ")->getHeight()/2,
		(float)ptMouse.x, (float)ptMouse.y);
	//angle = getAngle(x + TILEX / 2, y + TILEY / 2, m_enemy->getX(), m_enemy->getY());
	m_defaultBullet->update();

}

void defaultGun::render()
{
	DrawPng(m_defaultGunImage, m_graphics,(int)(m_x + IMAGEMANAGER->findImage("±ÇÃÑ")->getWidth() / 2),
			(int)(m_y + IMAGEMANAGER->findImage("±ÇÃÑ")->getHeight() / 2)
		, IMAGEMANAGER->findImage("±ÇÃÑ")->getWidth(), 
		IMAGEMANAGER->findImage("±ÇÃÑ")->getHeight(),angle);
	
	char text[64];
	wsprintf(text, "x : %d y : %d", ptMouse.x, ptMouse.y);

	TextOut(getMemDC(), 10, 100, text, strlen(text));



	sprintf(text, "angle : %.2f",angle * (180/PI));

	TextOut(getMemDC(), 10, 130, text, strlen(text));

	sprintf(text, "angle2 : %.2f", addAngle * (180 / PI));

	TextOut(getMemDC(), 10, 150, text, strlen(text));


	m_defaultBullet->render();
}

void defaultGun::fire()
{
}

void defaultGun::setAngle()
{
}

void defaultGun::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}
