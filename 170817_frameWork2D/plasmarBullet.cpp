#include "stdafx.h"
#include "plasmarBullet.h"


plasmarBullet::plasmarBullet()
{
}


plasmarBullet::~plasmarBullet()
{
}

void plasmarBullet::fire(int x, int y, float angle, float speed, CHARACTER playerType)
{
	bullet *temp = new bullet;
	temp->m_x = x;
	temp->m_y = y;
	temp->m_width = IMAGEMANAGER->findImage("플라즈마 총알")->getFrameWidth();
	temp->m_height = IMAGEMANAGER->findImage("플라즈마 총알")->getFrameHeight();
	temp->m_damage = 15;
	temp->m_range = 600;
	temp->m_gravity = 0.2f;
	temp->m_isGravity = 0;
	temp->m_speed = speed;
	temp->m_angle = angle;
	temp->m_image = IMAGEMANAGER->findImage("플라즈마 총알");
	temp->m_ani = ANIMATIONMANAGER->findAnimation("plasma");
	temp->m_playerType = playerType;
	m_vBullet.push_back(temp);
}

HRESULT plasmarBullet::init()
{
	return S_OK;
}

void plasmarBullet::release()
{
}

void plasmarBullet::update()
{
	for (m_viBullet = m_vBullet.begin(); m_viBullet != m_vBullet.end();)
	{
		(*m_viBullet)->m_isGravity += (*m_viBullet)->m_gravity;
		(*m_viBullet)->m_x += cosf((*m_viBullet)->m_angle) * (*m_viBullet)->m_speed;
		(*m_viBullet)->m_y += -sinf((*m_viBullet)->m_angle) * (*m_viBullet)->m_speed;
		(*m_viBullet)->m_ani->start();
		(*m_viBullet)->m_range -= (*m_viBullet)->m_speed;

		//(*m_viBullet)->m_speed -= 0.09f;


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

void plasmarBullet::render()
{
	for (m_viBullet = m_vBullet.begin(); m_viBullet != m_vBullet.end(); m_viBullet++)
	{
		(*m_viBullet)->m_image->aniRender(getMemDC(), (*m_viBullet)->m_x, (*m_viBullet)->m_y, (*m_viBullet)->m_ani);
	}
}

void plasmarBullet::delBullet(viBullet & delBullet)
{
	delBullet = m_vBullet.erase(delBullet);
}

int plasmarBullet::getBulletSize()
{
	if (m_vBullet.size() > 0) {
		return m_vBullet.size();
	}
	else
	{
		return 0;
	}
}
