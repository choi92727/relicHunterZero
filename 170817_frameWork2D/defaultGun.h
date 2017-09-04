#pragma once
#include "gunInterface.h"
#include "defaultBullet.h"
#include "defaultBullet.h"
class defaultGun : public gunInterface
{
private:
	defaultBullet* m_bullet;
public:
	defaultGun();
	~defaultGun();
	HRESULT init();
	void release();
	void update();
	void render();
	void fire();
	void setAngle();
	void setPosition(int x,int y);
};

