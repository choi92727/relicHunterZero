#include "stdafx.h"
#include "teleport.h"


teleport::teleport()
{
}


teleport::~teleport()
{
}

HRESULT teleport::init()
{
	IMAGEMANAGER->addImage("메인메뉴배경화면", "images/bg_menu_main.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	m_rc = RectMakeCenter(WINSIZEX/2, WINSIZEY/2, 150, 100);
	m_im = IMAGEMANAGER->findImage("텔레포트이펙트");
	frameX = 0;
	ANIMATIONMANAGER->addDefAnimation("텔레포트애니", "텔레포트이펙트", 10, false, true);
	m_ani = ANIMATIONMANAGER->findAnimation("텔레포트애니");
	ANIMATIONMANAGER->start("텔레포트애니");
	return S_OK;
}

void teleport::release()
{
}

void teleport::update()
{
	//frameX=10;
}

void teleport::render()
{
	IMAGEMANAGER->render("메인메뉴배경화면", getMemDC());
	m_im->aniAlphaRender(getMemDC(), m_rc.left, m_rc.top, m_ani,100);
	
	IMAGEMANAGER->render("텔레포트", getMemDC(), m_rc.left, m_rc.top);
}
