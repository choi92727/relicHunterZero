#include "stdafx.h"
#include "gunTestScene.h"


gunTestScene::gunTestScene()
{
}


gunTestScene::~gunTestScene()
{
}

HRESULT gunTestScene::init()
{
	m_defaultGun = new defaultGun();
	m_defaultGun->init();
	return S_OK;
}

void gunTestScene::release()
{
}

void gunTestScene::update()
{
	m_defaultGun->update();
}

void gunTestScene::render()
{
	//IMAGEMANAGER->render("±ÇÃÑ",getMemDC(),WINSIZEX/2,WINSIZEY/2);
	m_defaultGun->render();
}

