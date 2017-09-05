#pragma once
#include "bulletInterface.h"
class machineBullet : public bulletInterface
{
public:
	machineBullet();
	~machineBullet();
	void fire(int x, int y, float angle, float speed, CHARACTER playerType);
	HRESULT init();
	void release();
	void update();
	void render();
	void delBullet(viBullet &delBullet);
	int getBulletSize();

};

