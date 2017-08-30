#pragma once
#include "gameNode.h"
#include "tank.h"
#include "tankMap.h"
class tankGameScene :
	public gameNode
{
private:
	tankMap * m_tankMap;
	tank * m_tank;
public:
	tankGameScene();
	~tankGameScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

