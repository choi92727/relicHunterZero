#pragma once
#include "gunInterface.h"
#include "machineBullet.h"
class machineGun : public gunInterface
{
private:

public:
	machineGun();
	~machineGun();
	HRESULT init(CHARACTER playerType);
	void release();
	void update();
	void render();
	void fire();
	void setAngle();
	void setPosition(int x, int y);


};

