#include "stdafx.h"
#include "shotGun.h"


shotGun::shotGun()
{

}


shotGun::~shotGun()
{
}

HRESULT shotGun::init(CHARACTER playerType)
{
	m_damage = 10.0f;
	m_speed = 25.0f;
	m_angle = 0;
	m_x = 0;
	m_y = 0;
	m_fireDelay = 2.0f * 60.0f;
	m_isDelay = m_fireDelay;
	m_gunImage[0] = new Image(L"images/spr_shotgun_0.png");
	m_graphics = new Graphics(getMemDC());
	m_gunImage[1] = new Image(L"images/spr_shotgun_1.png");
	m_fire = true;
	m_playerType = playerType;

	return S_OK;
}

void shotGun::release()
{
	SAFE_DELETE_ARRAY(*m_gunImage);
	SAFE_DELETE(m_graphics);
}

void shotGun::update()
{
	setAngle();
}

void shotGun::render()
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
	sprintf(text, "%.2f", m_angle *(180 / PI));

	TextOut(getMemDC(), 10, 100, text, strlen(text));
}

void shotGun::fire()
{
	for (int i = 0; i < 6; i++) {
		m_bullet = new shotBullet;
		m_bullet->init();
		m_bullet->fire(m_x,
			m_y + IMAGEMANAGER->findImage("¼¦°Ç")->getHeight()
			, m_angle + ((i * 6) - 15) * PI / 180, m_speed, m_playerType);
		m_bulletManager->addBullet(*m_bullet);
	}
}

void shotGun::setAngle()
{
	m_angle = getAngle(m_x, m_y, ptMouse.x, ptMouse.y);

}

void shotGun::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}
