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


	SCENEMANAGER->changeScene("mapTool");


	
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
}

void mainGame::render()
{
	//��� �� ��Ʈ��
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	SCENEMANAGER->render();
	EFFECTMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	//=================================================
	//������� ������ HDC�� �׸���.(�̰͵� ������ ����!)
	this->getBackBuffer()->render(getHDC());

}



