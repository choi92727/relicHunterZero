#pragma once

//화면 왼쪽
#define TILESIZE 64
#define TILEX 50
#define TILEY 30

//화면 오른쪽 이미지 타일 갯수
#define SAMPLETILEX 47
#define SAMPLETILEY 3

//에너미
#define ENEMYMAX 100

//비트연산자 (and &, or |)
#define ATTR_UNMOVE 0x0000001
#define ATTR_POSITION 0x0000002

//지형
enum TERRAIN
{
	TR_NONE,
	TR_GROUND,
	TR_WALL
};

//오브젝트
enum OBJECT
{
	OBJ_NONE,
	OBJ_BOX1,
	OBJ_BOX2_1,
	OBJ_BOX2_2,
	OBJ_ROOT1_1,
	OBJ_ROOT1_2,
	OBJ_ROOT1_3,
	OBJ_ROOT2_1,
	OBJ_ROOT2_2,
	OBJ_ROOT2_3
};

//에너미
enum ENEMY
{
	ENM_NONE,
	ENM_TURTLE,
	ENM_DUCK,
	ENM_KAMIKAZE
};

//타일 구조체
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj = OBJ_NONE;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
	DWORD attribute;
};

struct tagCreateEnemy
{
	ENEMY enm = ENM_NONE;
	RECT rc;
	POINT pt;
};

//이미지 타일 구조체
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
	bool tileOn;
};

struct tagCurrentTile
{
	int x;
	int y;
};