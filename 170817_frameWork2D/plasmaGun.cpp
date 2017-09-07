#include "stdafx.h"
#include "plasmaGun.h"


plasmaGun::plasmaGun()
{
}


plasmaGun::~plasmaGun()
{
}

HRESULT plasmaGun::init(CHARACTER playerType)
{
	m_damage = 10.0f;
	m_speed = 10.0f;
	m_angle = 0;
	m_x = 0;
	m_y = 0;
	m_fireDelay = 1.5f * 60.0f;
	m_isDelay = m_fireDelay;
	m_gunImage[0] = new Image(L"images/spr_smg_plasma_0.png");
	m_graphics = new Graphics(getMemDC());
	m_gunImage[1] = new Image(L"images/spr_smg_plasma_1.png");
	m_fire = true;
	m_playerType = playerType;


	return S_OK;
}

void plasmaGun::release()
{
}

void plasmaGun::update()
{
	setAngle();


}

void plasmaGun::render()
{

	if (m_x <= ptMouse.x) {
		DrawPng(m_gunImage[0], m_graphics, m_x, m_y,
			IMAGEMANAGER->findImage("플라즈마")->getHeight(),IMAGEMANAGER->findImage("플라즈마")->getWidth(), m_angle);
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

void plasmaGun::fire()
{
	m_bullet = new plasmarBullet;
	m_bullet->init();
	m_bullet->fire(m_x, 
		m_y + IMAGEMANAGER->findImage("플라즈마")->getHeight() / 2
		, m_angle, m_speed, m_playerType);
	m_bulletManager->addBullet(*m_bullet);
}

void plasmaGun::setAngle()
{

	m_angle = getAngle(m_x, m_y, (float)ptMouse.x, (float)ptMouse.y);
}

void plasmaGun::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}
