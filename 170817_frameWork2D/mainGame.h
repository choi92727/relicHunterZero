#pragma once
#include "gameNode.h"
#include "loadingGame.h"
#include "gunTestScene.h"


class mainGame : public gameNode
{
private:
	//세이브,로드,지형,오브젝트,지우개
	

public:
	mainGame();
	~mainGame();

	HRESULT init();
	void release();
	void update();
	void render();

	

};

