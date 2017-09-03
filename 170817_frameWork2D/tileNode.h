#pragma once

//화면 왼쪽
#define TILESIZE 64
#define TILEX 50
#define TILEY 30

//화면 오른쪽 이미지 타일 갯수
#define SAMPLETILEX 47
#define SAMPLETILEY 3

//비트연산자 (and &, or |)
#define ATTR_UNMOVE 0x0000001
#define ATTR_POSITION 0x0000002

//지형
enum TERRAIN
{
	TR_GROUND,
	TR_WALL,
	TR_NONE
};

//오브젝트
enum OBJECT
{
	OBJ_BLOCK1,
	OBJ_BLOCK2,
	OBJ_ROOT1,
	OBJ_ROOT2,
	OBJ_NONE
};

//타일 구조체
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