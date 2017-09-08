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
	void render(POINT pt);
	void fire();
	void setPosition(int x, int y);



};

