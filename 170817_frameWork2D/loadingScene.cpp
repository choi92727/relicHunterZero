#include "stdafx.h"
#include "loadingScene.h"

loadingScene::loadingScene()
{
}

loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	m_loading = new loading;
	m_loading->init();

	this->totalLoading();

	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(m_loading);
}

void loadingScene::update()
{
	m_loading->update();
	//로딩 완료 후 씬전환
	if (m_loading->loadingDone())
	{
		//SCENEMANAGER->changeScene("scene1");
	}
}

void loadingScene::render()
{
	m_loading->render();
}

void loadingScene::totalLoading()
{
	for (int i = 0; i < 100; i++)
	{
		m_loading->loadImage("테스트", WINSIZEX, WINSIZEY);
	}
}
