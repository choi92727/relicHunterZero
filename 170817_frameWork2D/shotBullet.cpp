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
	m_width = IMAGEMANAGER->findImage("���� �Ѿ�")->getWidth();
	m_height = IMAGEMANAGER->findImage("���� �Ѿ�")->getHeight() - 5;
	m_x = x;
	m_y = y - m_height / 2;
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

void shotBullet::render(POINT pt)
{
	Rectangle(getMemDC(), m_x, m_y, m_x + m_width, m_y + m_height / 2);


	DrawPng(m_bulletImage, m_graphics, m_x - pt.x, m_y - m_width / 2 - pt.y, m_height, m_width, m_angle);

	char text[64];

	wsprintf(text, "%d,%d", m_x, m_y);

	TextOut(getMemDC(), m_x - pt.x, m_y - pt.y, text, strlen(text));


}
