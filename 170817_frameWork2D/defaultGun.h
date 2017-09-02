#pragma once
#include "gunInterface.h"
class defaultGun : public gunInterface
{
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

