#pragma once
#include "gameNode.h"
#include "loadingGame.h"



class mainGame : public gameNode
{
private:
	//���̺�,�ε�,����,������Ʈ,���찳
	

public:
	mainGame();
	~mainGame();

	HRESULT init();
	void release();
	void update();
	void render();

	

};

