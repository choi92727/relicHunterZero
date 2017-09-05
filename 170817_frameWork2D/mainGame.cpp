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
	SCENEMANAGER->addScene("loadingGame", new loadingGame);
	SCENEMANAGER->addScene("mainMenu", new mainMenu);
	SCENEMANAGER->addScene("mapTool", new mapTool);
	SCENEMANAGER->addScene("creditScene", new creditScene);
	SCENEMANAGER->addScene("selectScene", new selectScene);
	SCENEMANAGER->changeScene("loadingGame");

	m_cd = new cursorDraw;
	m_cd->init(0);

	m_add = new addImage;
	m_add->init();

	
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
	//��� �� ��Ʈ��
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	SCENEMANAGER->render();
	EFFECTMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	m_cd->render();
	//=================================================
	//������� ������ HDC�� �׸���.(�̰͵� ������ ����!)
	this->getBackBuffer()->render(getHDC());

}



