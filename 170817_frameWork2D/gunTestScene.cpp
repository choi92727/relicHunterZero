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
	return S_OK;
}

void gunTestScene::release()
{
}

void gunTestScene::update()
{
}

void gunTestScene::render()
{
	IMAGEMANAGER->render("ฑวรั",getMemDC(),WINSIZEX/2,WINSIZEY/2);
}

