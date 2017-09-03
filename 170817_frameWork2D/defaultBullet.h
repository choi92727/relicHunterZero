#pragma once
#include "bulletInterface.h"
class defaultBullet : public bulletInterface
{
private:
	Image* m_defaultBullet;
	Graphics* m_graphics;
public:
	defaultBullet();
	~defaultBullet();

	HRESULT init();
	void release();
	void update();
	void render();
	void fire(int x, int y, float angle, float speed);

};

