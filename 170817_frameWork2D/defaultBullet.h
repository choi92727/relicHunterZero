#pragma once
#include "bulletInterface.h"
class defaultBullet : public bulletInterface
{
private:
	
public:
	defaultBullet();
	~defaultBullet();
	 void fire(int x, int y, float angle, float speed, CHARACTER playerType);
	 HRESULT init();
	 void release();
	 void update();
	 void render();


};

