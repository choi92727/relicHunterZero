#pragma once
#include "bulletInterface.h"
class collisionBullet : public bulletInterface
{
public:
	collisionBullet();
	~collisionBullet();
	HRESULT init(CHARACTER _char,RECT rc,float damage);
	void release();
	void update();
	void render();
	void render(POINT pt);
	void setRect(RECT rc);
};

