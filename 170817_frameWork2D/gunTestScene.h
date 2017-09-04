#pragma once
#include "gameNode.h"
#include "defaultGun.h"
#include "machineGun.h"
#include "shotGun.h"
class gunTestScene : public gameNode
{
private:
	RECT m_rc;
	gunInterface* m_defaultGun;
	CHARACTER m_character;
public:
	gunTestScene();
	~gunTestScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

