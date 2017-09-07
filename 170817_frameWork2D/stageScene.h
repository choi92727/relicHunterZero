#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "numberDrawManager.h"
#include "bulletManager.h"
#include "gunInterface.h"
#include "defaultGun.h"
#include "characterManager.h"
#include "enemyManager.h"

class stageScene :
	public gameNode
{
private:
	tagTile tile[TILEY][TILEX];
	tagCreateEnemy m_createEnemy[ENEMYMAX];
	bool tileOn[TILEY][TILEX];

	int speed;
	RECT Character_Rc;
	POINT Charcter_pt;
	POINT currentCamera;
	POINT Charcter_Real_pt;
	RECT camera_rc;
	bulletManager *m_bulletManager;//ºÒ·¿ ¸Å´ÏÀú
	gunInterface *m_defaultGun;
	characterManager *m_cm;
	enemyManager* m_enemyManager;

	numberDrawManager *testNumber;
public:
	stageScene();
	~stageScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void loadStage(char* mapName);
	void loadEnermy(char* mapName);

	void moveCamera(POINT characterPt);
};

