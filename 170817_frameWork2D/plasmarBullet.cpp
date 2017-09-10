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
	m_x = x;
	m_y = y;
	m_width = IMAGEMANAGER->findImage("플라즈마 총알")->getFrameWidth();
	m_height = IMAGEMANAGER->findImage("플라즈마 총알")->getFrameHeight();
	m_damage = 15;
	m_range = 600;
	m_gravity = 0.2f;
	m_isGravity = 0;
	m_speed = speed;
	m_angle = angle;
	m_image = IMAGEMANAGER->findImage("플라즈마 총알");
	m_ani = ANIMATIONMANAGER->findAnimation("plasma");
	m_playerType = playerType;

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

	if (m_range < 300)
	{
		m_x += cos(m_angle) * (m_speed / 2);
		m_y += -sin(m_angle) * (m_speed / 2);

	}
	else
	{
		m_x += cos(m_angle) * m_speed;
		m_y += -sin(m_angle) * m_speed;
	}


	m_range -= m_speed;



	m_ani->start();

}

void plasmarBullet::render(POINT pt)
{

	/*Rectangle(getMemDC(), m_x, m_y, m_x + m_image->getFrameWidth(), m_y + m_image->getFrameHeight());*/

	m_image->aniRender(getMemDC(), m_x - pt.x, m_y - pt.y, m_ani);

	//char text[64];

	//wsprintf(text, "%d,%d", m_x, m_y);

	//TextOut(getMemDC(), m_x - pt.x, m_y - pt.y, text, strlen(text));
}


