#pragma once

//ȭ�� ����
#define TILESIZE 64
#define TILEX 50
#define TILEY 30

//ȭ�� ������ �̹��� Ÿ�� ����
#define SAMPLETILEX 47
#define SAMPLETILEY 3

//��Ʈ������ (and &, or |)
#define ATTR_UNMOVE 0x0000001
#define ATTR_POSITION 0x0000002

//����
enum TERRAIN
{
	TR_GROUND,
	TR_WALL,
	TR_NONE
};

//������Ʈ
enum OBJECT
{
	OBJ_BLOCK1,
	OBJ_BLOCK2,
	OBJ_ROOT1,
	OBJ_ROOT2,
	OBJ_NONE
};

//Ÿ�� ����ü
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
	DWORD attribute;
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