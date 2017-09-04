#pragma once
#include "gunInterface.h"
#include "plasmarBullet.h"
class plasmaGun : public gunInterface
{
private:
	plasmarBullet* m_bullet;
public:
	plasmaGun();
	~plasmaGun();
	HRESULT init(CHARACTER playerType);
	void release();
	void update();
	void render();
	void fire();
	void setAngle();
	void setPosition(int x, int y);
};

