#pragma once
#include "gunInterface.h"
#include "machineBullet.h"
class machineGun : public gunInterface
{
private:
	machineBullet* m_bullet;
public:
	machineGun();
	~machineGun();
	HRESULT init();
	void release();
	void update();
	void render();
	void fire();
	void setAngle();
	void setPosition(int x, int y);
};

