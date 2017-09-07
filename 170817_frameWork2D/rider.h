#pragma once
#include "characterInterface.h"
class rider : public characterInterface
{
private:
	int number = 0;
	int count = 0;
public:
	rider();
	~rider();

	HRESULT init(POINT position);
	void release();
	void update();
	void render();

	void animation();
	void move();
	void melee();
	void hit();
	void dead();
	void fire();

};

