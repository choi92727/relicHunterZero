#pragma once
#include "gunInterface.h"
class defaultGun : public gunInterface
{
private:
	Image* m_defaultGunImage;
	Graphics* m_graphics;
	float addAngle = 0;
	float angle;
public:
	defaultGun();
	~defaultGun();
	HRESULT init();
	void release();
	void update();
	void render();
	void fire();
	void setAngle();
};

