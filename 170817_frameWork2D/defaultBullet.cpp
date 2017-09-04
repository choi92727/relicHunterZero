#include "stdafx.h"
#include "defaultBullet.h"


defaultBullet::defaultBullet()
{
}


defaultBullet::~defaultBullet()
{
}

void defaultBullet::fire(int x, int y, float angle, float speed, CHARACTER playerType)
{
	bullet *temp = new bullet;
	temp->m_x = x;
	temp->m_y = y;
	temp->m_width = IMAGEMANAGER->findImage("±âº» ÃÑ¾Ë")->getWidth();
	temp->m_height = IMAGEMANAGER->findImage("±âº» ÃÑ¾Ë")->getHeight();
	temp->m_damage = 15;
	temp->m_range = 600;
	temp->m_speed = speed;
	temp->m_angle = angle;
	temp->m_playerType = playerType;

	m_vBullet.push_back(temp);
}

HRESULT defaultBullet::init()
{

	m_bulletImage = new Image(L"images/spr_bullet_small_1.png");
	m_graphics = new Graphics(getMemDC());
	return S_OK;
}

void defaultBullet::release()
{
}

void defaultBullet::update()
{
	for (m_viBullet = m_vBullet.begin(); m_viBullet != m_vBullet.end();)
	{
		(*m_viBullet)->m_x += cos((*m_viBullet)->m_angle) * (*m_viBullet)->m_speed;
		(*m_viBullet)->m_y += -sin((*m_viBullet)->m_angle) * (*m_viBullet)->m_speed;

		(*m_viBullet)->m_range -= (*m_viBullet)->m_speed;
		if ((*m_viBullet)->m_x > WINSIZEX || (*m_viBullet)->m_range < 0)
		{
			delBullet(m_viBullet);
		}
		else
		{
			m_viBullet++;
		}
	}
}

void defaultBullet::render()
{
	for (m_viBullet = m_vBullet.begin(); m_viBullet != m_vBullet.end();m_viBullet++)
	{
		DrawPng(m_bulletImage, m_graphics, (*m_viBullet)->m_x, (*m_viBullet)->m_y, (*m_viBullet)->m_height, (*m_viBullet)->m_width,(*m_viBullet)->m_angle);
	}
}

void defaultBullet::delBullet(viBullet & delBullet)
{
	delBullet = m_vBullet.erase(delBullet);

}





