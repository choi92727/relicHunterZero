#pragma once
#include "gameNode.h"
#include "teleport.h"
class alphaTest :
	public gameNode
{
private:
	teleport* m_tp;
	
public:
	alphaTest();
	~alphaTest();

	HRESULT init();
	
	void release();
	void update();
	void render();
	
};

