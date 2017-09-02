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
	loading=IMAGEMANAGER->addFrameImage("로딩화면", "images/loadingScene.bmp", 15360, 720, 12, 1, true, RGB(255, 0, 255));
	ANIMATIONMANAGER->addDefAnimation("ani1", "로딩화면", 10, false, true);
	ANIMATIONMANAGER->start("ani1");
	loadingAni= ANIMATIONMANAGER->findAnimation("ani1");

	m_addImage = new addImage;
	m_addImage->init();

	return S_OK;
}

void loadingGame::release()
{
	SAFE_DELETE(m_addImage);
}

void loadingGame::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SCENEMANAGER->changeScene("gunTest");
	}
}

void loadingGame::render()
{
	loading->aniRender(getMemDC(), 0, 0, loadingAni);
}
