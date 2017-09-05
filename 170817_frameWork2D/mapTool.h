#pragma once
#include "gameNode.h"
#include "tileNode.h"

class mapTool : public gameNode
{
private:
	tagTile tile[TILEY][TILEX];
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

	POINT currentShowPt;

	bool sampleTile, sampleObject, sampleEnemy;
	bool loookSample;
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

	//������Ʈ ��ġ
	void createObject();
	//���ʹ� ��ġ
	void createEnemy();

	void moveSample_left();
	void moveSample_right();

	void saveLoad();

	void pushEnemyMemory();
};

