#include "stdafx.h"
#include "shotBullet.h"


shotBullet::shotBullet()
{
}


shotBullet::~shotBullet()
{
}

void shotBullet::fire(int x, int y, float angle, float speed)
{
	for (int i = 0; i < 6; i++)
	{
		bullet *temp = new bullet;
		temp->m_x = x;
		temp->m_y = y;
		temp->m_width = IMAGEMANAGER->findImage("���� �Ѿ�")->getWidth();
		temp->m_height = IMAGEMANAGER->findImage("���� �Ѿ�")->getHeight();
		temp->m_damage = 15;
		temp->m_range = 350;
		temp->m_speed = speed;
		temp->m_angle = angle + ((i*3-15) * PI/180);
		m_vBullet.push_back(temp);
	}
	
}

HRESULT shotBullet::init()
{
	m_bulletImage = new Image(L"images/spr_bullet_1.png");
	m_graphics = new Graphics(getMemDC());
	return S_OK;
}

void shotBullet::release()
{
}

void shotBullet::update()
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

void shotBullet::render()
{
	for (m_viBullet = m_vBullet.begin(); m_viBullet != m_vBullet.end(); m_viBullet++)
	{
		DrawPng(m_bulletImage, m_graphics, (*m_viBullet)->m_x, (*m_viBullet)->m_y, (*m_viBullet)->m_height, (*m_viBullet)->m_width, (*m_viBullet)->m_angle);
	}
}

void shotBullet::delBullet(viBullet & delBullet)
{
	delBullet = m_vBullet.erase(delBullet);

}
