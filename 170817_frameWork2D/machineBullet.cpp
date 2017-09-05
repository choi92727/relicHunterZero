#include "stdafx.h"
#include "machineBullet.h"


machineBullet::machineBullet()
{
}


machineBullet::~machineBullet()
{
}

void machineBullet::fire(int x, int y, float angle, float speed, CHARACTER playerType)
{
	bullet *temp = new bullet;
	temp->m_x = x;
	temp->m_y = y;
	temp->m_width = IMAGEMANAGER->findImage("±âº» ÃÑ¾Ë")->getWidth();
	temp->m_height = IMAGEMANAGER->findImage("±âº» ÃÑ¾Ë")->getHeight();
	temp->m_damage = 15;
	temp->m_range = 750;
	temp->m_speed = speed;
	temp->m_angle = angle;
	temp->m_playerType = playerType;
	m_vBullet.push_back(temp);
}

HRESULT machineBullet::init()
{
	m_bulletImage = new Image(L"images/spr_bullet_small_1.png");
	m_graphics = new Graphics(getMemDC());
	return S_OK;
}

void machineBullet::release()
{

}

void machineBullet::update()
{
	for (m_viBullet = m_vBullet.begin(); m_viBullet != m_vBullet.end();)
	{
		(*m_viBullet)->m_x += cos((*m_viBullet)->m_angle) * (*m_viBullet)->m_speed;
		(*m_viBullet)->m_y += -sin((*m_viBullet)->m_angle) * (*m_viBullet)->m_speed;

		(*m_viBullet)->m_range -= (*m_viBullet)->m_speed;
		if ((*m_viBullet)->m_x > WINSIZEX || (*m_viBullet)->m_range < 0 || (*m_viBullet)->m_x <  0)
		{
			delBullet(m_viBullet);
		}
		else
		{
			m_viBullet++;
		}
	}
}

void machineBullet::render()
{
	for (m_viBullet = m_vBullet.begin(); m_viBullet != m_vBullet.end(); m_viBullet++)
	{
		Rectangle(getMemDC(), (*m_viBullet)->m_x, (*m_viBullet)->m_y, (*m_viBullet)->m_x + (*m_viBullet)->m_width, (*m_viBullet)->m_y + (*m_viBullet)->m_height);
	
		DrawPng(m_bulletImage, m_graphics, (*m_viBullet)->m_x, (*m_viBullet)->m_y, (*m_viBullet)->m_height, (*m_viBullet)->m_width, (*m_viBullet)->m_angle);
	}
}

void machineBullet::delBullet(viBullet & delBullet)
{
	delBullet = m_vBullet.erase(delBullet);

}

int machineBullet::getBulletSize()
{
	if (m_vBullet.size() > 0) {
		return m_vBullet.size();
	}
	else
	{
		return 0;
	}
}
