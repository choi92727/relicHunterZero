#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()
{
	gameNode::init(true);
	m_cd = new cursorDraw;
	m_cd->init(0);

	m_add = new addImage;
	m_add->init();

	m_addS = new addSounds;
	m_addS->init();
	SCENEMANAGER->addScene("loadingGame", new loadingGame);
	SCENEMANAGER->addScene("mainMenu", new mainMenu);
	SCENEMANAGER->addScene("mapTool", new mapTool);
	SCENEMANAGER->addScene("creditScene", new creditScene);
	SCENEMANAGER->addScene("selectScene", new selectScene);
	SCENEMANAGER->addScene("stageScene", new stageScene);
	SCENEMANAGER->addScene("testScene", new testScene);
	SCENEMANAGER->addScene("alphaTest", new alphaTest);


	SCENEMANAGER->changeScene("loadingGame");


	
	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
}

void mainGame::update()
{
	gameNode::update();
	SCENEMANAGER->update();
	EFFECTMANAGER->update();
	ANIMATIONMANAGER->update();
	m_cd->reload();
}

void mainGame::render()
{
	//흰색 빈 비트맵
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	SCENEMANAGER->render();
	EFFECTMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	m_cd->render();
	//=================================================
	//백버퍼의 내용을 HDC에 그린다.(이것도 지우지 말것!)
	this->getBackBuffer()->render(getHDC());

}



