#pragma once
#include "gameNode.h"
#include "characterManager.h"
#include "itemManager.h"
class testScene :public gameNode
{
private:
	characterManager* m_player;
	itemManager* m_itemManager;
	POINT ptpt;
	RECT rcrc;
public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void collisionDetect();
};

