#pragma once
#include "loadingGame.h"
#include "gameNode.h"
#include "addImage.h"

class loadingGame : public gameNode
{
private:
	image *loading;
	animation* loadingAni;
	addImage* m_addImage;
public:
	loadingGame();
	~loadingGame();

	HRESULT init();
	void release();
	void update();
	void render();
};