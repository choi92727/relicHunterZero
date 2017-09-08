#pragma once

//ȭ�� ����
#define TILESIZE 64
#define TILEX 50
#define TILEY 30

//ȭ�� ������ �̹��� Ÿ�� ����
#define SAMPLETILEX 47
#define SAMPLETILEY 3

//������Ʈ
#define OBJECTMAX 100

//���ʹ�
#define ENEMYMAX 100

//��Ʈ������ (and &, or |)
#define ATTR_UNMOVE 0x0000001
#define ATTR_POSITION 0x0000002

//����
enum TERRAIN
{
	TR_NONE,
	TR_GROUND,
	TR_WALL
};

//������Ʈ
enum OBJECT
{
	OBJ_NONE,
	OBJ_BOX1,
	OBJ_BOX2,
	OBJ_ROOT1,
	OBJ_ROOT2,
	OBJ_TELEPORT
};

//���ʹ�
enum ENEMY
{
	ENM_NONE,
	ENM_TURTLE,
	ENM_DUCK,
	ENM_KAMIKAZE
};

//Ÿ�� ����ü
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

//�̹��� Ÿ�� ����ü
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