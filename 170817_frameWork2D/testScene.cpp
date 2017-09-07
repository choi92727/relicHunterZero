#include "stdafx.h"
#include "testScene.h"
#include "characterClassic.h"
testScene::testScene()
{
}


testScene::~testScene()
{
}

HRESULT testScene::init()
{
	POINT temp = { WINSIZEX / 2,WINSIZEY / 2 };
	m_player = new characterManager;
	m_player->init(temp, JIMMY);
	return S_OK;
}

void testScene::release()
{
	m_player->release();
}

void testScene::update()
{
	m_player->update();
}

void testScene::render()
{
	m_player->render();
}
