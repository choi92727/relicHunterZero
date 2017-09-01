#pragma once
#include "gameNode.h"
class mapToolScene :
	public gameNode
{
public:
	mapToolScene();
	~mapToolScene();


	HRESULT init();
	void release();
	void update();
	void render();
};

