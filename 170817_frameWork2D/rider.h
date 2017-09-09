#pragma once
#include "characterInterface.h"
class rider : public characterInterface
{
private:
	int number = 0;
	int count = 0;

	int runDelay = 0;

	int shieldCount = 0;
	int shieldRenderTemp = 0;
	int shieldRenderCount = 0;

	int bullet_damage = 0;
public:
	rider();
	~rider();

	HRESULT init(POINT position);
	void release();
	void update(POINT pt);
	void render(POINT pt);

	void animation();
	void move();
	void melee(POINT pt);
	void hit();
	void dead();
	void fire();
	void hpFaceInfo();
	void run();
	void shieldRegen();
	void damage();

	void damageBullet(float damage);
};

