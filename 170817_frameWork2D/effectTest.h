#pragma once
#include "gameNode.h"

class effectTest : public gameNode
{
public:
	effectTest();
	~effectTest();

	HRESULT init();
	void release();
	void update();
	void render();
};

