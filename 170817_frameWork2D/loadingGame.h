#pragma once
#include "loadingGame.h"
#include "gameNode.h"

class loadingGame : public gameNode
{
private:
	image *loading;
	animation* loadingAni;
public:
	loadingGame();
	~loadingGame();

	HRESULT init();
	void release();
	void update();
	void render();
};