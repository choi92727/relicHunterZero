#pragma once
#include "gameNode.h"
#include "loadingGame.h"
#include "addImage.h"
#include "mainMenu.h"
#include "mapTool.h"
#include "creditScene.h"



class mainGame : public gameNode
{
private:
	//���̺�,�ε�,����,������Ʈ,���찳
	addImage* m_add;

public:
	mainGame();
	~mainGame();

	HRESULT init();
	void release();
	void update();
	void render();

	

};

