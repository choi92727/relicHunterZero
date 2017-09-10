#pragma once
#include "characterClassic.h"

struct tagStageNode
{
	int stage;
	selectCharacter characterName;
	int HP;
	int currentBullet, maxBullet;
};