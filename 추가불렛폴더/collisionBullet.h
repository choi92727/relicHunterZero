#pragma once
#include "bulletInterface.h"
class collisionBullet : public bulletInterface
{
public:
	collisionBullet();
	~collisionBullet();
	HRESULT init(CHARACTER _char,RECT rc,float damage,float angle,float speed,float range);
	void release();
	void update();
	void render();
	void render(POINT pt);
	void setRect(RECT rc);
	RECT getRect() { return m_rc; }
};

