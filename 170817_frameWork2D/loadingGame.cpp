#include "stdafx.h"
#include "loadingGame.h"


loadingGame::loadingGame()
{
}


loadingGame::~loadingGame()
{
}

HRESULT loadingGame::init()
{
	loading=IMAGEMANAGER->addFrameImage("�ε�ȭ��", "images/loadingScene.bmp", 15360, 720, 12, 1, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addDefAnimation("ani1", "�ε�ȭ��", 10, false, true);
	ANIMATIONMANAGER->start("ani1");
	loadingAni= ANIMATIONMANAGER->findAnimation("ani1");
	SOUNDMANAGER->play("�ε����", 0.5f);
	return S_OK;
}

void loadingGame::release()
{
	SOUNDMANAGER->stop("�ε����");
}

void loadingGame::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SCENEMANAGER->changeScene("mainMenu");
	}
}

void loadingGame::render()
{
	loading->aniRender(getMemDC(), 0, 0, loadingAni);
}
