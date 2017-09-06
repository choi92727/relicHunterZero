#pragma once
#include "bulletInterface.h"
class plasmarBullet : public bulletInterface
{
private:

public:
	plasmarBullet();
	~plasmarBullet();
	void fire(int x, int y, float angle, float speed, CHARACTER playerType);
	HRESULT init();
	void release();
	void update();
	void render();


};

