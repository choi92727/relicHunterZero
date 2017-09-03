#pragma once
#include "gameNode.h"
#include "tileNode.h"

class mapTool : public gameNode
{
private:
	tagTile tile[TILEY][TILEX];
	bool tileOn[TILEY][TILEX];
	tagSampleTile tileButton[SAMPLETILEY][SAMPLETILEX];
	int currentTileButton;
	tagCurrentTile currentTile;

	RECT buttonUI;
	RECT moveRC[2];
	RECT saveRC[4];
	RECT loadRC[4];

	POINT currentShowPt;

	BOOL loookSample;

	int sampleX;
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

	void moveSample_left();
	void moveSample_right();

	void saveLoad();
};

