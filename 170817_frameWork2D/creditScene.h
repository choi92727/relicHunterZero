#pragma once
#include "gameNode.h"
class creditScene :
	public gameNode
{
private:
	int y;
public:
	creditScene();
	~creditScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

