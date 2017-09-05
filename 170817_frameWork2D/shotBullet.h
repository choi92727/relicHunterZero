#pragma once
#include "bulletInterface.h"
class shotBullet : public bulletInterface
{
private:

public:
	shotBullet();
	~shotBullet();
	void fire(int x, int y, float angle, float speed, CHARACTER playerType);
	HRESULT init();
	void release();
	void update();
	void render();
	void delBullet(viBullet &delBullet);
	int getBulletSize();

};

