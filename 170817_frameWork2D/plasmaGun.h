#pragma once
#include "gunInterface.h"
#include "plasmarBullet.h"
class plasmaGun : public gunInterface
{
private:
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
	bulletInterface* getBullet() {
		return m_bullet;
	};

};

