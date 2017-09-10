#pragma once
#include "characterInterface.h"
class jimmy : public characterInterface
{
private:
	int number = 0;
	int count = 0;

	int runDelay = 0;

	int shieldCount = 0;
	int shieldRenderTemp = 0;
	int shieldRenderCount = 0;

	int bullet_damage = 0;

	bool soundTeleportOnce = true;

	bool deathOnce = true;
	bool walkOnce = true;			//사운드한번실행
	bool runOnce = true;			//사운드한번실행
	bool shieldBreakOnce = true;	//사운드한번실행
	bool shieldRegenOnce = true;	//

	bool RECTrender;
public:
	jimmy();
	~jimmy();

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

	void isTeleport();
};

