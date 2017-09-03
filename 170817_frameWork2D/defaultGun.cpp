#include "stdafx.h"
#include "defaultGun.h"


defaultGun::defaultGun()
{
}


defaultGun::~defaultGun()
{
}

HRESULT defaultGun::init()
{
	m_defaultGunImage = new Image(L"images/spr_pistol_jimmy_0.bmp");
	m_graphics = new Graphics(getMemDC());

	return S_OK;
}

void defaultGun::release()
{
}

void defaultGun::update()
{


	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		addAngle -= 1 * (PI / 180);
	}
	
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		addAngle += 1 * (PI / 180);
	}

	//angle = getAngle(WINSIZEX/2 + IMAGEMANAGER->findImage("±ÇÃÑ")->getWidth(), WINSIZEY / 2 + IMAGEMANAGER->findImage("±ÇÃÑ")->getHeight(),ptMouse.x,ptMouse.y);
}

void defaultGun::render()
{
	DrawPng(m_defaultGunImage, m_graphics, WINSIZEX / 2, WINSIZEY / 2,
		IMAGEMANAGER->findImage("±ÇÃÑ")->getWidth(), IMAGEMANAGER->findImage("±ÇÃÑ")->getHeight(),addAngle);
	
	char text[64];
	wsprintf(text, "x : %d y : %d", ptMouse.x, ptMouse.y);

	TextOut(getMemDC(), 10, 10, text, strlen(text));
	LineMake(getMemDC(),WINSIZEX / 2 + IMAGEMANAGER->findImage("±ÇÃÑ")->getWidth()/2,
		WINSIZEY / 2 + IMAGEMANAGER->findImage("±ÇÃÑ")->getHeight() /2,
		WINSIZEX / 2 + IMAGEMANAGER->findImage("±ÇÃÑ")->getWidth() / 2 + cos(addAngle) * 100, 
		WINSIZEY / 2 + IMAGEMANAGER->findImage("±ÇÃÑ")->getHeight() / 2 + -sin(addAngle) * 100);


	sprintf(text, "angle : %.2f",addAngle * (180/PI));

	TextOut(getMemDC(), 10, 100, text, strlen(text));

}

void defaultGun::fire()
{
}

void defaultGun::setAngle()
{
}
