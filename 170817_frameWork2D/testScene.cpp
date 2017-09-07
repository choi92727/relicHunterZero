#include "stdafx.h"
#include "testScene.h"


testScene::testScene()
{
}


testScene::~testScene()
{
}

HRESULT testScene::init()
{
	m_tp = new teleport;
	m_tp->init();
	return S_OK;
}

void testScene::release()
{

}

void testScene::update()
{
	m_tp->update();
}

void testScene::render()
{
	m_tp->render();
}
