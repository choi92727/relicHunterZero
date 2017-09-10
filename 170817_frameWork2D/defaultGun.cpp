#include "stdafx.h"
#include "defaultGun.h"


defaultGun::defaultGun()
{
}


defaultGun::~defaultGun()
{
}

HRESULT defaultGun::init(CHARACTER playerType)
{
	m_damage = 10.0f;
	m_speed = 5.0f;
	m_angle = 0;
	m_x = 0;
	m_y = 0;
	m_fireDelay = 0.5f * 60.0f;
	m_isDelay = m_fireDelay;
	m_gunImage[0] = new Image(L"images/spr_pistol_jimmy_0.png");
	m_graphics = new Graphics(getMemDC());
	m_gunImage[1] = new Image(L"images/spr_pistol_jimmy_1.png");
	m_fire = true;
	m_playerType = playerType;
	m_gunType = GUN_DEFAULT;
	m_currentBullet = 30;
	m_maxBullet = 30;
	m_totalBullet = 270;
	m_currentDraw.init("ÃÑ¾Ë¼ýÀÚ", 2);
	m_totalDraw.init("º°¼ýÀÚ", 3);

	return S_OK;
}

void defaultGun::release()
{
	SAFE_DELETE_ARRAY(*m_gunImage);
	SAFE_DELETE(m_graphics);
	SAFE_DELETE(m_bulletManager);
}

void defaultGun::update()
{
	if (m_playerType == CHAR_PLAYER) {
		m_currentDraw.update(m_currentBullet);
		m_totalDraw.update(m_totalBullet);
	}
	if (CHAR_ENEMY)
	{
		if (!m_enemy_fire)
		{
			m_enemyfireDelay -= 1.0f;
			if (m_enemyfireDelay < 0)
			{
				m_enemy_fire = true;
				m_enemyfireDelay = 1.5f * 60.0f;
			}
		}
	}

}

void defaultGun::render()
{
	
		if (m_x <= ptMouse.x) {
			DrawPng(m_gunImage[0], m_graphics, m_x, m_y,
				22, 60, m_angle);
		}
		else
		{
			DrawPng(m_gunImage[1], m_graphics, m_x, m_y,
				22, 60, m_angle);
		}

		char text[64];
		sprintf(text, "%.2f", getFireDelay());

		TextOut(getMemDC(), 10, 100, text, strlen(text));
	

}

void defaultGun::render(POINT pt)
{
	
	if (m_playerType == CHAR_PLAYER) {
		if (WINSIZEX / 2 <= ptMouse.x) {
			DrawPng(m_gunImage[0], m_graphics, m_x - pt.x, m_y - pt.y,
				22, 60, m_angle);
		}
		else
		{
			DrawPng(m_gunImage[1], m_graphics, m_x - pt.x, m_y - pt.y,
				22, 60, m_angle);
		}
	}
	else if (m_playerType == CHAR_ENEMY) {
		if (m_angle > 0) {
			DrawPng(m_gunImage[0], m_graphics, m_x - pt.x, m_y - pt.y,
				22, 60, m_angle);
		}
		else
		{
			DrawPng(m_gunImage[1], m_graphics, m_x - pt.x, m_y - pt.y,
				22, 60, m_angle);
		}
	}

		if (m_playerType == CHAR_PLAYER) {

		char text[64];
		sprintf(text, "%.2f", getFireDelay());

		TextOut(getMemDC(), 10, 100, text, strlen(text));


		IMAGEMANAGER->render("±ÇÃÑ½Ç·ç¿§", getMemDC(), 10, WINSIZEY - 50);

		m_currentDraw.render(150, WINSIZEY - 70, 15);
		m_totalDraw.render(230, WINSIZEY - 100, 15);
	}

}

void defaultGun::fire()
{
	if (m_currentBullet > 0) {
		m_bullet = new defaultBullet;
		m_bullet->init();
		m_bullet->fire(
			m_x,
			m_y + IMAGEMANAGER->findImage("±ÇÃÑ")->getHeight() / 2
			, m_angle, m_speed, m_playerType);

		m_bulletManager->addBullet(*m_bullet);
		if (m_playerType == CHAR_PLAYER) {
			m_currentBullet--;
		}
	}	
}



void defaultGun::setPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}






