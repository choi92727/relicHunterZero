#include "stdafx.h"
#include "creditScene.h"


creditScene::creditScene()
{
}


creditScene::~creditScene()
{
}

HRESULT creditScene::init()
{
	IMAGEMANAGER->addImage("크레딧", "Images/크레딧.bmp", 1280, 1000);
	SOUNDMANAGER->play("테란브금", 0.5f);
	y = 0;
	return S_OK;
}

void creditScene::release()
{
	SOUNDMANAGER->stop("테란브금");
}

void creditScene::update()
{
	if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		SCENEMANAGER->changeScene("mainMenu");
	y++;
}

void creditScene::render()
{
	RECT temp = RectMake(0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->loopRender("크레딧", getMemDC(), &temp, 0, y);
}
