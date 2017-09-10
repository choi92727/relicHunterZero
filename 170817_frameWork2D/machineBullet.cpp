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

	m_x = x;
	m_y = y;
	m_width = IMAGEMANAGER->findImage("±âº» ÃÑ¾Ë")->getWidth();
	m_height = IMAGEMANAGER->findImage("±âº» ÃÑ¾Ë")->getHeight();
	m_damage = 15;
	m_range = 750;
	m_speed = speed;
	m_angle = angle;
	m_playerType = playerType;

}

HRESULT machineBullet::init()
{
	m_bulletImage = new Image(L"images/spr_bullet_small_1.png");
	m_graphics = new Graphics(getMemDC());
	return S_OK;
}

void machineBullet::release()
{
	SAFE_DELETE(m_bulletImage);
	SAFE_DELETE(m_graphics);
}

void machineBullet::update()
{
	m_x += cos(m_angle) * m_speed;
	m_y += -sin(m_angle) * m_speed;
	m_range -= m_speed;
}

void machineBullet::render(POINT pt)
{
	/*Rectangle(getMemDC(), m_x, m_y, m_x + m_width, m_y + m_height / 2);*/


	DrawPng(m_bulletImage, m_graphics, m_x - pt.x, m_y - m_width / 2 - pt.y, m_height, m_width, m_angle);

	//char text[64];

	//wsprintf(text, "%d,%d", m_x, m_y);

	//TextOut(getMemDC(), m_x - pt.x, m_y - pt.y, text, strlen(text));
}



