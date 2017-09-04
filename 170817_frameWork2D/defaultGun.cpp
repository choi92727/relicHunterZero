#include "stdafx.h"
#include "defaultGun.h"


defaultGun::defaultGun()
{
}


defaultGun::~defaultGun()
{
}

HRESULT defaultGun::init()
{
	m_damage = 10.0f;
	m_speed = 10.0f;
	m_angle = 0;
	m_x = 0;
	m_y = 0;
	m_fireDelay = 1.5f * 60.0f;
	m_isDelay = m_fireDelay;
	m_gunImage = new Image(L"images/spr_pistol_jimmy_0.png");
	m_graphics = new Graphics(getMemDC());
	m_fire = true;


	m_bullet = new defaultBullet;
	m_bullet->init();


	return S_OK;
}

void defaultGun::release()
{
}

void defaultGun::update()
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

void defaultGun::render()
{
	DrawPng(m_gunImage, m_graphics, m_x, m_y,
		22, 60, m_angle);
	m_bullet->render();

	char text[64];
	sprintf(text, "%.2f", m_angle *(180 / PI));

	TextOut(getMemDC(), 10, 100, text, strlen(text));


}

void defaultGun::fire()
{
	m_bullet->fire(m_x, m_y, m_angle, m_speed);
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

