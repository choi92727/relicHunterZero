#pragma once
#include "gameNode.h"
class gunTestScene : public gameNode
{
public:
	gunTestScene();
	~gunTestScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

