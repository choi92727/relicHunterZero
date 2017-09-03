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
	m_rc = RectMake(WINSIZEX / 2, WINSIZEY / 2, 80, 80);
	m_defaultGun = new defaultGun();
	m_defaultGun->init((m_rc.left + m_rc.right)/2,(m_rc.top + m_rc.bottom)/2- 50);
	return S_OK;
}

void gunTestScene::release()
{
}

void gunTestScene::update()
{
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

	m_defaultGun->setPosition((m_rc.left + m_rc.right) / 2, (m_rc.top + m_rc.bottom) / 2 - 50);

	m_defaultGun->update();
}

void gunTestScene::render()
{
	//IMAGEMANAGER->render("±ÇÃÑ",getMemDC(),WINSIZEX/2,WINSIZEY/2);
	Rectangle(getMemDC(), m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	m_defaultGun->render();
}

