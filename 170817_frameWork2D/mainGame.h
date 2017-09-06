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



class mainGame : public gameNode
{
private:
	//���̺�,�ε�,����,������Ʈ,���찳
	addImage* m_add;
	cursorDraw* m_cd;
	addSounds* m_addS;
public:
	mainGame();
	~mainGame();

	HRESULT init();
	void release();
	void update();
	void render();

	

};

