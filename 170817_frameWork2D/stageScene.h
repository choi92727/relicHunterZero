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

#include "collisionBullet.h"

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
	bulletManager *m_bulletManager;//불렛 매니저
	gunInterface *m_defaultGun;
	characterManager *m_cm;
	enemyManager* m_enemyManager;
	objectManager* m_objectManager;

	numberDrawManager *testNumber;

	vector<gunInterface*> m_enemyGun;
	
	
	int testX ;
	int tileX, tileY;

	bool p_meleeToggle = false;	//근접공격시 공격프레임에만 실행되도록함
	bool p_meleeOnce = true;	//근접공격 한번만실행
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
	void collision_tile_Enemy();
	void collision_Object_character();
	void collision_Object_Enemy();

	void enemyGunRender();
	void enemyGunSetPosition();
	void enemyShotGun();
	void enemyDeadCheck();
	
};

