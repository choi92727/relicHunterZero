#pragma once
#include "gameNode.h"
#include "teleport.h"
class testScene :
	public gameNode
{
private:
	teleport* m_tp;
public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

