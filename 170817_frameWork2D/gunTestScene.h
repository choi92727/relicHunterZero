#pragma once
#include "gameNode.h"
#include "defaultGun.h"
#include "machineGun.h"
#include "shotGun.h"
#include "plasmaGun.h"
#include "bulletManager.h"
#include "defaultBullet.h"
#include "bulletInterface.h"
class gunTestScene : public gameNode
{
private:
	RECT m_rc;
	bulletInterface* m_bullet;
	gunInterface* m_defaultGun;
	CHARACTER m_character;
	POINT pt_list[20];
	bulletManager* m_bulletManager;
	float fireDelay;
	float isDelay;
	bool fire;
public:
	gunTestScene();
	~gunTestScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

