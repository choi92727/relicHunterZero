#include "stdafx.h"
#include "cursorDraw.h"


cursorDraw::cursorDraw()
{
}


cursorDraw::~cursorDraw()
{
}

HRESULT cursorDraw::init(int x)
{
	/*SetCursor(NULL);
	ShowCursor(FALSE);*/
	IMAGEMANAGER->addFrameImage("커서이미지", "Images/aimCursor.bmp", 588, 42, 14, 1, true, RGB(255, 0, 255));
	cursor_im = IMAGEMANAGER->findImage("커서이미지");
	int arrLen[] = { 0 };
	ANIMATIONMANAGER->addAnimation("cursor1", "커서이미지", arrLen, 1, 5, false);
	int arrLen1[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
	ANIMATIONMANAGER->addAnimation("cursor2", "커서이미지", arrLen1, 13, 5, false);
	cursor_ani = ANIMATIONMANAGER->findAnimation("cursor1");
	return S_OK;
}

void cursorDraw::release()
{
}

void cursorDraw::update()
{
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		cursor_ani = ANIMATIONMANAGER->findAnimation("cursor2");
		ANIMATIONMANAGER->start("cursor2");
		
	}
	if (cursor_ani->isPlay() == false)
	{
		cursor_ani = ANIMATIONMANAGER->findAnimation("cursor1");
	}
	
}

void cursorDraw::render()
{
	cursor_im->aniRender(getMemDC(), ptMouse.x- cursor_im->getFrameWidth()/2, ptMouse.y - cursor_im->getFrameHeight() / 2, cursor_ani);
}
