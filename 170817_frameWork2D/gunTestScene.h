#pragma once
#include "gameNode.h"
#include "defaultGun.h"
class gunTestScene : public gameNode
{
private:
	defaultGun* m_defaultGun;
public:
	gunTestScene();
	~gunTestScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

