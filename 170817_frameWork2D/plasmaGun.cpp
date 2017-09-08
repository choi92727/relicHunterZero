#include "stdafx.h"
#include "plasmaGun.h"


plasmaGun::plasmaGun()
{
}


plasmaGun::~plasmaGun()
{
}

HRESULT plasmaGun::init(CHARACTER playerType)
{
	m_damage = 10.0f;
	m_speed = 10.0f;
	m_angle = 0;
	m_x = 0;
	m_y = 0;
	m_fireDelay = 1.5f * 60.0f;
	m_isDelay = m_fireDelay;
	m_gunImage[0] = new Image(L"images/spr_smg_plasma_0.png");
	m_graphics = new Graphics(getMemDC());
	m_gunImage[1] = new Image(L"images/spr_smg_plasma_1.png");
	m_fire = true;
	m_playerType = playerType;
	m_gunType = GUN_DEFAULT;
	m_currentBullet = 15;
	m_maxBullet = 15;
	m_totalBullet = 150;
	m_currentDraw.init("총알숫자", 2);
	m_totalDraw.init("별숫자", 3);


	return S_OK;
}

void plasmaGun::release()
{
}

void plasmaGun::update()
{

	m_currentDraw.update(m_currentBullet);
	m_totalDraw.update(m_totalBullet);

}

void plasmaGun::render(POINT pt)
{

	if (WINSIZEX / 2 <= ptMouse.x) {
		DrawPng(m_gunImage[0], m_graphics, m_x - pt.x, m_y - pt.y,
			24, 60, m_angle);
	}
	else
	{
		DrawPng(m_gunImage[1], m_graphics, m_x - pt.x, m_y - pt.y,
			24, 60, m_angle);
	}

	char text[64];
	sprintf(text, "%.2f", getFireDelay());

	TextOut(getMemDC(), 10, 100, text, strlen(text));


	IMAGEMANAGER->render("플라즈마실루엣", getMemDC(), 10, WINSIZEY - 50);

	m_currentDraw.render(150, WINSIZEY - 70, 15);
	m_totalDraw.render(230, WINSIZEY - 100, 15);



}

void plasmaGun::fire()
{
	if (m_currentBullet > 0) {
		m_bullet = new plasmarBullet;
		m_bullet->init();
		m_bullet->fire(m_x,
			m_y + IMAGEMANAGER->findImage("플라즈마")->getHeight() / 2
			, m_angle, m_speed, m_playerType);
		m_bulletManager->addBullet(*m_bullet);
		m_currentBullet--;
	}
}
void plasmaGun::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}
