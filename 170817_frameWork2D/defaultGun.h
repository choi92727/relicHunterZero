#pragma once
#include "gunInterface.h"
#include "defaultBullet.h"
class defaultGun : public gunInterface
{
private:
	Image* m_defaultGunImage;
	Graphics* m_graphics;
	float addAngle = 0;
	float angle = 0;
	defaultBullet* m_defaultBullet;
public:
	defaultGun();
	~defaultGun();
	HRESULT init(int x,int y);
	void release();
	void update();
	void render();
	void fire();
	void setAngle();
	void setPosition(int x,int y);
};

