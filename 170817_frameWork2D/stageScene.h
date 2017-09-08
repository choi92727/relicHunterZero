#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "numberDrawManager.h"
#include "bulletManager.h"
#include "gunInterface.h"
#include "defaultGun.h"
#include "shotGun.h"
#include "plasmaGun.h"
#include "machineGun.h"
#include "characterManager.h"
#include "enemyManager.h"
#include "objectManager.h"

class stageScene :
	public gameNode
{
private:
	tagTile tile[TILEY][TILEX];
	tagCreateEnemy m_createEnemy[ENEMYMAX];
	tagCreateObject m_createObject[OBJECTMAX];
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
	objectManager* m_objectManager;

	numberDrawManager *testNumber;

	vector<gunInterface*> m_enemyGun;
	
	
	int testX ;
	int tileX, tileY;
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

	void collision_tile_character();
	void collision_tile_Eneermy();
	void collision_Object_character();
	
	void enemyGunRender();
	void enemyGunSetPosition();
	void enemyShotGun();
	
};

