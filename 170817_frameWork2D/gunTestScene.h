#pragma once
#include "gameNode.h"
#include "defaultGun.h"
class gunTestScene : public gameNode
{
private:
	RECT m_rc;
	defaultGun* m_defaultGun;
	CHARACTER m_character;
public:
	gunTestScene();
	~gunTestScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

