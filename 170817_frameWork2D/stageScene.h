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
#include "charcterGetItem.h"
#include "itemManager.h"
#include "stageNode.h"
#include "cursorDraw.h"
#include "collisionBullet.h"
#include "noneGun.h"
class stageScene :
	public gameNode
{
private:
	cursorDraw* m_cd;
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
	charcterGetItem* m_charcterGetItem;
	numberDrawManager *testNumber;
	itemManager* m_itemManager;

	vector<gunInterface*> m_enemyGun;


	gunInterface* player_guns[4];

	tagStageNode m_stageNode[1];
	int testX ;
	int tileX, tileY;

	bool p_meleeToggle = false;   //근접공격시 공격프레임에만 실행되도록함
	bool p_meleeOnce = true;   //근접공격 한번만실행

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


	//에너미 생성관련 함수
	void createEnemyGun() {}

	//캐릭터 근접공격 함수
	//
	void charMelee()
	{
		if (KEYMANAGER->isStayKeyDown('V'))
		{
			p_meleeToggle = true;
		}

		if (p_meleeToggle)
		{
			if (m_cm->getMeleeAtk() && p_meleeOnce)
			{
				m_bulletManager->addCollisionBullet(CHAR_PLAYER, m_cm->getMelee_atkRc(), 90, m_cm->getP_Angle(), m_cm->getSpeed(), m_cm->getSpeed() * 14);
				p_meleeOnce = false;
			}
			if (m_cm->getMeleeEnd()) { p_meleeToggle = false; }
		}

		if (!p_meleeToggle) p_meleeOnce = true;
	}

	//캐릭터 총기 및 총알 관련 함수
	void getIsReload();
	
	void changeWeapon();



	void collision_tile_character();
	void collision_tile_Enemy();
	void collision_Object_character();
	void collision_Object_Enemy();

	void collision_item_detect();
	void collision_item_real();


	void enemyGunRender();
	
	void enemyShotGun();

	void enemyDeadCheck();

	
	void dropItem();
	void stageClear();
	void loadPlayerAndStage();
};

