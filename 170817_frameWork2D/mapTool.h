#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "enemyManager.h"
#include "objectManager.h"

class mapTool : public gameNode
{
private:
	tagTile tile[TILEY][TILEX];
	tagCreateObject m_createObject[OBJECTMAX];
	tagCreateEnemy m_createEnemy[ENEMYMAX];
	bool tileOn[TILEY][TILEX];
	tagSampleTile sampleButton[SAMPLETILEY][SAMPLETILEX];
	int currentTileButton;
	tagCurrentTile currentTile;

	RECT buttonUI;
	RECT moveRC[2];
	RECT tileRC;
	RECT exitRC;
	RECT objectRC;
	RECT enemyRC;
	RECT saveRC[4];
	RECT loadRC[4];

	bool drawCenter;

	POINT currentShowPt;

	bool sampleTile, sampleObject, sampleEnemy;
	bool loookSample;

	objectManager* m_objectManager;
	enemyManager* m_enemyManager;
public:
	mapTool();
	~mapTool();

	HRESULT init();
	void release();
	void update();
	void render();

	void tileMove();
	void tileCheck();
	void tileClick();

	//오브젝트 설치
	void createObject();
	//에너미 설치
	void createEnemy();

	void moveSample_left();
	void moveSample_right();

	void saveLoad();

	void pushEnemyMemory();
};
