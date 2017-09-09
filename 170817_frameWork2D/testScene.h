#pragma once
#include "gameNode.h"
#include "characterManager.h"
class testScene :public gameNode
{
private:
	characterManager* m_player;
public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

