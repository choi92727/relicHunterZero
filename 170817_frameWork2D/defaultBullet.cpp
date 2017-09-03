#include "stdafx.h"
#include "defaultBullet.h"


defaultBullet::defaultBullet()
{
}


defaultBullet::~defaultBullet()
{
}

HRESULT defaultBullet::init()
{
	m_defaultBullet = new Image(L"images/spr_bullet_small_1.png");
	m_graphics = new Graphics(getMemDC());

	return S_OK;
}

void defaultBullet::release()
{
}

void defaultBullet::update()
{
	for (auto i = m_vBullet.begin(); i != m_vBullet.end();)
	{
		i->x += cos(i->m_angle) * i->m_speed;
		i->y += -sin(i->m_angle) * i->m_speed;

		if (i->x > WINSIZEX)
		{
			i = m_vBullet.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void defaultBullet::render()
{
	for (auto i = m_vBullet.begin(); i != m_vBullet.end(); ++i)
	{
		DrawPng(m_defaultBullet, m_graphics, i->x, i->y, 30, 46, i->m_angle);
	}
}

void defaultBullet::fire(int x, int y, float angle, float speed)
{
	bullet temp;
	temp.x = x;
	temp.y = y;
	temp.m_angle = angle;
	temp.m_speed = speed;
	
	m_vBullet.push_back(temp);
}


