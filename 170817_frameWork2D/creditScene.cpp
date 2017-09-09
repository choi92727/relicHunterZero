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
	IMAGEMANAGER->addImage("ũ����", "Images/ũ����.bmp", 1280, 1000);
	SOUNDMANAGER->play("�׶����", 0.5f);
	y = 0;
	return S_OK;
}

void creditScene::release()
{
	SOUNDMANAGER->stop("�׶����");
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
	IMAGEMANAGER->loopRender("ũ����", getMemDC(), &temp, 0, y);
}
