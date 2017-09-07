#include "stdafx.h"
#include "defaultGun.h"


defaultGun::defaultGun()
{
}


defaultGun::~defaultGun()
{
}

HRESULT defaultGun::init(CHARACTER playerType)
{
	m_damage = 10.0f;
	m_speed = 15.0f;
	m_angle = 0;
	m_x = 0;
	m_y = 0;
	m_fireDelay = 0.5f * 60.0f;
	m_isDelay = m_fireDelay;
	m_gunImage[0] = new Image(L"images/spr_pistol_jimmy_0.png");
	m_graphics = new Graphics(getMemDC());
	m_gunImage[1] = new Image(L"images/spr_pistol_jimmy_1.png");
	m_fire = true;
	m_playerType = playerType;


	return S_OK;
}

void defaultGun::release()
{
	SAFE_DELETE_ARRAY(*m_gunImage);
	SAFE_DELETE(m_graphics);
	SAFE_DELETE(m_bulletManager);
}

void defaultGun::update()
{
	setAngle();
}

void defaultGun::render()
{
	if (m_x <= ptMouse.x) {
		DrawPng(m_gunImage[0], m_graphics, m_x, m_y,
			22, 60, m_angle);
	}
	else
	{
		DrawPng(m_gunImage[1], m_graphics, m_x, m_y,
			22, 60, m_angle);
	}

	char text[64];
	sprintf(text, "%.2f", getFireDelay());

	TextOut(getMemDC(), 10, 100, text, strlen(text));


}

void defaultGun::fire()
{
	m_bullet = new defaultBullet;
	m_bullet->init();
	m_bullet->fire(
		m_x,
		m_y + IMAGEMANAGER->findImage("±ÇÃÑ")->getHeight()/2
		, m_angle, m_speed,m_playerType);

	m_bulletManager->addBullet(*m_bullet);

}

void defaultGun::setAngle()
{
	m_angle = getAngle(m_x, m_y, ptMouse.x, ptMouse.y);
}

void defaultGun::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}






