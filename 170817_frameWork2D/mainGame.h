#pragma once
#include "gameNode.h"
#include "loadingGame.h"
#include "addImage.h"
#include "mainMenu.h"
#include "mapTool.h"
#include "creditScene.h"
#include "selectScene.h"
#include "cursorDraw.h"
#include "stageScene.h"
#include "addSounds.h"
#include "testScene.h"
#include "alphaTest.h"




class mainGame : public gameNode
{
private:
	//세이브,로드,지형,오브젝트,지우개
	addImage* m_add;
	addSounds* m_addS;
public:
	mainGame();
	~mainGame();

	HRESULT init();
	void release();
	void update();
	void render();

	

};

