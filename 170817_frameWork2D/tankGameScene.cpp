#include "stdafx.h"
#include "tankGameScene.h"


tankGameScene::tankGameScene()
{
}


tankGameScene::~tankGameScene()
{
}

HRESULT tankGameScene::init()
{
	m_tankMap = new tankMap;
	m_tankMap->init();

	m_tank = new tank;
	m_tank->init();
	m_tank->setTankMapMemoryLink(m_tankMap);
	m_tank->setTankPosition();
	return S_OK;
}

void tankGameScene::release()
{
	SAFE_DELETE(m_tank);
	SAFE_DELETE(m_tankMap);
}

void tankGameScene::update()
{
	m_tankMap->update();
	m_tank->update();
}

void tankGameScene::render()
{
	m_tankMap->render();
	m_tank->render();
}
