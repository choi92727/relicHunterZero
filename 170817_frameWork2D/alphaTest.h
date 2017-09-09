#pragma once
#include "gameNode.h"

class alphaTest :
	public gameNode
{
private:
	
	
public:
	alphaTest();
	~alphaTest();

	HRESULT init();
	
	void release();
	void update();
	void render();
	
};

