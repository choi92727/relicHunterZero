#include "stdafx.h"
#include "shotGun.h"


shotGun::shotGun()
{

}


shotGun::~shotGun()
{
}

HRESULT shotGun::init(CHARACTER playerType)
{
	m_damage = 10.0f;
	m_speed = 25.0f;
	m_angle = 0;
	m_x = 0;
	m_y = 0;
	m_fireDelay = 2.0f * 60.0f;
	m_isDelay = m_fireDelay;
	m_gunImage[0] = new Image(L"images/spr_shotgun_0.png");
	m_graphics = new Graphics(getMemDC());
	m_gunImage[1] = new Image(L"images/spr_shotgun_1.png");
	m_fire = true;
	m_playerType = playerType;
	m_gunType = GUN_SHOTGUN;
	m_currentBullet = 8;
	m_maxBullet = 8;
	m_totalBullet = 40;
	m_currentDraw.init("ÃÑ¾Ë¼ýÀÚ", 2);
	m_totalDraw.init("º°¼ýÀÚ", 3);
	return S_OK;
}

void shotGun::release()
{
	SAFE_DELETE_ARRAY(*m_gunImage);
	SAFE_DELETE(m_graphics);
}

void shotGun::update()
{
	setAngle();
	m_currentDraw.update(m_currentBullet);
	m_totalDraw.update(m_totalBullet);
}

void shotGun::render(POINT pt)
{

	if (WINSIZEX / 2 <= ptMouse.x) {
		DrawPng(m_gunImage[0], m_graphics, m_x - pt.x, m_y - pt.y,
			22, 60, m_angle);
	}
	else
	{
		DrawPng(m_gunImage[1], m_graphics, m_x - pt.x, m_y - pt.y,
			22, 60, m_angle);
	}

	char text[64];
	sprintf(text, "%.2f", getFireDelay());

	TextOut(getMemDC(), 10, 100, text, strlen(text));


	IMAGEMANAGER->render("¼¦°Ç½Ç·ç¿§", getMemDC(), 10, WINSIZEY - 50);

	m_currentDraw.render(150, WINSIZEY - 70, 15);
	m_totalDraw.render(230, WINSIZEY - 100, 15);

}

void shotGun::fire()
{
	if (m_currentBullet > 0) {
		for (int i = 0; i < 6; i++) {
			m_bullet = new shotBullet;
			m_bullet->init();
			m_bullet->fire(
				m_x,
				m_y + IMAGEMANAGER->findImage("¼¦°Ç")->getHeight() / 2
				, m_angle + ((i * 6) - 15) * PI / 180, m_speed, m_playerType);

			m_bulletManager->addBullet(*m_bullet);
		}
	}
	m_currentBullet--;
}

void shotGun::setAngle()
{
	m_angle = getAngle(WINSIZEX / 2, WINSIZEY / 2, ptMouse.x, ptMouse.y);


}

void shotGun::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}
