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
	m_speed = 10.0f;
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
	m_bullet = new defaultBullet;
	m_bullet->init();


	return S_OK;
}

void defaultGun::release()
{
	m_bullet->release();
	SAFE_DELETE(m_bullet);
	SAFE_DELETE_ARRAY(*m_gunImage);
	SAFE_DELETE(m_graphics);
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
	if (m_x <= ptMouse.x) {
		DrawPng(m_gunImage[0], m_graphics, m_x, m_y,
			22, 60, m_angle);
	}
	else
	{
		DrawPng(m_gunImage[1], m_graphics, m_x, m_y,
			22, 60, m_angle);
	}
	m_bullet->render();

	char text[64];
	sprintf(text, "%.2f", getFireDelay());

	TextOut(getMemDC(), 10, 100, text, strlen(text));


}

void defaultGun::fire()
{
	m_bullet->fire(m_x, m_y, m_angle, m_speed,m_playerType);
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






