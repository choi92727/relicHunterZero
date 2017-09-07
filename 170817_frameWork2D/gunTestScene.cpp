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

	//구동순서
	//1.총 생성
	//2.초기화=CARACTER변수를 같이 넣어줘서 누구의 총인지 확인
	//3.불렛 매니저를 총에다가 넣어줌(총이 발사될 때마다 불렛매니저에 총의 포인터를 넣어줌);
	m_bulletManager = new bulletManager;
	isDelay = 0;
	fireDelay = 0;
	m_character = CHAR_PLAYER;
	m_rc = RectMake(WINSIZEX / 2, WINSIZEY / 2, 80, 80);
	m_defaultGun = new defaultGun;
	m_defaultGun->init(m_character);
	m_defaultGun->setBulletManagerLink(*m_bulletManager);
	fire = false;

	return S_OK;
}

void gunTestScene::release()
{
}

void gunTestScene::update()
{
	fireDelay = m_defaultGun->getFireDelay();


	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		//m_defaultGun->release();
		m_defaultGun = new machineGun;
		m_defaultGun->init(m_character);
		m_defaultGun->setBulletManagerLink(*m_bulletManager);
		fire = true;
		isDelay = 0;
	}

	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		//m_defaultGun->release();

		m_defaultGun = new defaultGun;
		m_defaultGun->init(m_character);
		m_defaultGun->setBulletManagerLink(*m_bulletManager);
		fire = true;
		isDelay = 0;
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		//m_defaultGun->release();

		m_defaultGun = new shotGun;
		m_defaultGun->init(m_character);
		m_defaultGun->setBulletManagerLink(*m_bulletManager);
		fire = true;
		isDelay = 0;
	}

	if (KEYMANAGER->isOnceKeyDown('R'))
	{
	//	m_defaultGun->release();

		m_defaultGun = new plasmaGun;
		m_defaultGun->init(m_character);
		m_defaultGun->setBulletManagerLink(*m_bulletManager);
		fire = true;
		isDelay = 0;
	}

	for (int i = 1; i < 20; i++)
	{
		pt_list[i].x = pt_list[i - 1].x;
		pt_list[i].y = pt_list[i - 1].y;
	}

	if (fire)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			m_defaultGun->fire();
			fire = false;
		}
	}
	else
	{
		isDelay++;
		if (isDelay == fireDelay)
		{
			fire = true;
			isDelay = 0;
		}
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

	m_defaultGun->setPosition(pt_list[19].x,pt_list[19].y - 20);//

	m_defaultGun->update();

	m_bulletManager->update();
	
}

void gunTestScene::render()
{
	//IMAGEMANAGER->render("권총",getMemDC(),WINSIZEX/2,WINSIZEY/2);
	Rectangle(getMemDC(), m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	m_defaultGun->render();
	m_bulletManager->render();


	char txt[64];
	sprintf(txt, "delay : %.2f", m_defaultGun->getFireDelay());
	TextOut(getMemDC(), 10, 150, txt, strlen(txt));

	sprintf(txt, "isdelay : %.2f", isDelay);
	TextOut(getMemDC(), 10, 170, txt, strlen(txt));
	

	if (fire)
	{
		TextOut(getMemDC(), 10, 190, "발사가능", strlen("발사가능"));
	}
	else
	{
		TextOut(getMemDC(), 10, 190, "발사불가능", strlen("발사불가능"));

	}


}

