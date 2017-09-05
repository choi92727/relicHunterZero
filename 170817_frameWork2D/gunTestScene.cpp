#include "stdafx.h"
#include "gunTestScene.h"


gunTestScene::gunTestScene()
{
}


gunTestScene::~gunTestScene()
{
}

HRESULT gunTestScene::init()
{
	m_bulletManager = new bulletManager;
	m_bullet = new defaultBullet;
	m_bullet->init();
	m_character = CHAR_PLAYER;
	m_rc = RectMake(WINSIZEX / 2, WINSIZEY / 2, 80, 80);
	m_defaultGun = new defaultGun;
	m_defaultGun->init(m_character);
	m_bulletManager->addBullet(*m_defaultGun->m_bullet);
	return S_OK;
}

void gunTestScene::release()
{
}

void gunTestScene::update()
{

	m_bulletManager->update();

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		m_defaultGun = new machineGun;
		m_defaultGun->init(m_character);
		m_bulletManager->addBullet(*m_defaultGun->m_bullet);

	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		m_defaultGun = new defaultGun;
		m_defaultGun->init(m_character);
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		m_defaultGun = new shotGun;
		m_defaultGun->init(m_character);
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		m_defaultGun = new plasmaGun;
		m_defaultGun->init(m_character);
	}

	for (int i = 1; i < 20; i++)
	{
		pt_list[i].x = pt_list[i - 1].x;
		pt_list[i].y = pt_list[i - 1].y;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_rc.left -= 3;
		m_rc.right -= 3;

	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_rc.left += 3;
		m_rc.right += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		m_rc.top -= 3;
		m_rc.bottom -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		m_rc.top += 3;
		m_rc.bottom += 3;
	}

	pt_list[0].x = (m_rc.left + m_rc.right) / 2;
	pt_list[0].y = (m_rc.top + m_rc.bottom) / 2;

	m_defaultGun->setPosition(pt_list[19].x,pt_list[19].y - 20);

	m_defaultGun->update();
	
}

void gunTestScene::render()
{
	//IMAGEMANAGER->render("±ÇÃÑ",getMemDC(),WINSIZEX/2,WINSIZEY/2);
	Rectangle(getMemDC(), m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	m_defaultGun->render();
	m_bulletManager->render();

}

