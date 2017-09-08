#pragma once
#include "gunInterface.h"
#include "shotBullet.h"
class shotGun : public gunInterface
{
private:
public:
	shotGun();
	~shotGun();
	HRESULT init(CHARACTER playerType);
	void release();
	void update();
	void render(POINT pt);
	void fire();
	void setPosition(int x, int y);


};

