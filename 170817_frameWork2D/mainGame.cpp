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
	SCENEMANAGER->addScene("gunTest",new gunTestScene);
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



