#include "stdafx.h"
#include "effectTest.h"


effectTest::effectTest()
{
}


effectTest::~effectTest()
{
}

HRESULT effectTest::init()
{
	EFFECTMANAGER->addEffect("气惯1", "Images/explosion1.bmp", 832, 62, 32, 62, 1, 0.3f, 100);
	EFFECTMANAGER->addEffect("气惯2", "Images/explosion2.bmp", 4355, 135, 335, 135, 1, 0.3f, 100);
	return S_OK;
}

void effectTest::release()
{
}

void effectTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) EFFECTMANAGER->play("气惯1", ptMouse.x, ptMouse.y);
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) EFFECTMANAGER->play("气惯2", ptMouse.x, ptMouse.y);
}

void effectTest::render()
{
}
