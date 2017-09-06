#include "stdafx.h"
#include "shotBullet.h"


shotBullet::shotBullet()
{
}


shotBullet::~shotBullet()
{
}

void shotBullet::fire(int x, int y, float angle, float speed, CHARACTER playerType)
{
		m_width = IMAGEMANAGER->findImage("¼¦°Ç ÃÑ¾Ë")->getWidth();
		m_height = IMAGEMANAGER->findImage("¼¦°Ç ÃÑ¾Ë")->getHeight() - 5;
		m_x = x;
		m_y = y - m_height/2;
		m_damage = 15;
		m_range = 250;
		m_speed = speed;
		m_angle = angle;
		m_playerType = playerType;
}

HRESULT shotBullet::init()
{
	m_bulletImage = new Image(L"images/spr_bullet_1.png");
	m_graphics = new Graphics(getMemDC());
	return S_OK;
}

void shotBullet::release()
{
	SAFE_DELETE(m_bulletImage);
	SAFE_DELETE(m_graphics);
}

void shotBullet::update()
{
	m_x += cos(m_angle) * m_speed;
	m_y += -sin(m_angle) * m_speed;
	m_range -= m_speed;
}

void shotBullet::render()
{
	Rectangle(getMemDC(), m_x, m_y, m_x + m_width, m_y + m_height);


	DrawPng(m_bulletImage, m_graphics, m_x, m_y, m_height, m_width, m_angle);


}
