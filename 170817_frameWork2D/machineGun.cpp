#include "stdafx.h"
#include "machineGun.h"


machineGun::machineGun()
{
}


machineGun::~machineGun()
{
}

HRESULT machineGun::init(CHARACTER playerType)
{
	m_damage = 10.0f;
	m_speed = 15.0f;
	m_angle = 0;
	m_x = 0;
	m_y = 0;
	m_fireDelay = 0.1f * 60.0f;
	m_isDelay = m_fireDelay;
	m_gunImage[0] = new Image(L"images/spr_machinegun_0.png");
	m_graphics = new Graphics(getMemDC());
	m_gunImage[1] = new Image(L"images/spr_machinegun_1.png");
	m_fire = true;
	m_playerType = playerType;

	m_bullet = new machineBullet;
	m_bullet->init();


	return S_OK;
}

void machineGun::release()
{
}

void machineGun::update()
{
	setAngle();
	if (m_fire)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			fire();
			m_fire = false;
		}
	}
	else
	{
		m_isDelay--;
		if (m_isDelay < 0)
		{
			m_isDelay = m_fireDelay;
			m_fire = true;
		}
	}
	m_bullet->update();
}

void machineGun::render()
{
	if (m_x <= ptMouse.x) {
		DrawPng(m_gunImage[0], m_graphics, m_x, m_y,
			24, 60, m_angle);
	}
	else
	{
		DrawPng(m_gunImage[1], m_graphics, m_x, m_y,
			24, 60, m_angle);
	}
	m_bullet->render();
	char text[64];
	sprintf(text, "%.2f", m_angle *(180 / PI));

	TextOut(getMemDC(), 10, 100, text, strlen(text));

}

void machineGun::fire()
{
	m_bullet->fire(m_x, m_y, m_angle, m_speed, m_playerType);

}

void machineGun::setAngle()
{
	m_angle = getAngle(m_x, m_y, ptMouse.x, ptMouse.y);

}

void machineGun::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}
