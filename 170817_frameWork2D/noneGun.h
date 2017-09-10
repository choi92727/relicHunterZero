#pragma once
#include "gunInterface.h"
class noneGun : public gunInterface
{
public:
	noneGun();
	~noneGun();
	HRESULT init(CHARACTER playerType);
	void release();
	void update();
	void render(POINT pt);
	void fire();
	void setPosition(int x, int y);
};

