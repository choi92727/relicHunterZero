#pragma once
#include "gunInterface.h"
#include "defaultBullet.h"

class defaultGun : public gunInterface
{
private:
public:
	defaultGun();
	~defaultGun();
	HRESULT init(CHARACTER playerType);
	void release();
	void update();
	void render();
	void fire();
	void setAngle();
	void setPosition(int x,int y);


	

};

