#pragma once
#include "bulletInterface.h"
class defaultBullet : public bulletInterface
{
private:
	
public:
	defaultBullet();
	~defaultBullet();
	 void fire(int x, int y, float angle, float speed);
	 HRESULT init();
	 void release();
	 void update();
	 void render();
	 void delBullet(viBullet &delBullet);


};

