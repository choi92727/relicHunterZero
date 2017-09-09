#pragma once

//화면 왼쪽
#define TILESIZE 64
#define TILEX 50
#define TILEY 30

//화면 오른쪽 이미지 타일 갯수
#define SAMPLETILEX 47
#define SAMPLETILEY 3

//오브젝트
#define OBJECTMAX 100

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
	OBJ_BOX2,
	OBJ_ROOT1,
	OBJ_ROOT2,
	OBJ_TELEPORT
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
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
	DWORD attribute;
};

struct tagCreateObject
{
	OBJECT obj = OBJ_NONE;
	RECT rc;
	POINT pt;
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