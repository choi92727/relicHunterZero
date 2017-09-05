#include "stdafx.h"
#include "stageScene.h"


stageScene::stageScene()
{
}


stageScene::~stageScene()
{
}

HRESULT stageScene::init()
{
	loadStage("tileMap1.map");
	testNumber = new numberDrawManager;
	testNumber->init("�Ѿ˼���", 5);

	currentCamera = { 0,0 };
	Charcter_pt = { WINSIZEX / 2,WINSIZEY / 2 };
	Character_Rc= RectMake(Charcter_pt.x, Charcter_pt.y, 50, 100);
	camera_rc = RectMake(currentCamera.x, currentCamera.y,1280,720);
	speed = 3;

	return S_OK;
}

void stageScene::release()
{
}

void stageScene::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		Charcter_pt.x-= speed;

	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		Charcter_pt.x += speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		Charcter_pt.y -= speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		Charcter_pt.y += speed;
	}
	currentCamera = { Charcter_pt.x - 640,Charcter_pt.y - 360 };
	camera_rc = RectMake(currentCamera.x, currentCamera.y, 1280, 720);

	RECT temp;
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			if (IntersectRect(&temp, &tile[y][x].rc, &camera_rc))
			{
				tileOn[y][x] = true;
			}
			else
			{
				tileOn[y][x] = false;
			}
		}
	}
	testNumber->update(Charcter_pt.x);
}

void stageScene::render()
{
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			if (tileOn[y][x])
			{
				IMAGEMANAGER->frameRender("����", getMemDC(), tile[y][x].rc.left- currentCamera.x, tile[y][x].rc.top - currentCamera.y, tile[y][x].terrainFrameX, tile[y][x].terrainFrameY);
				
				
			}
		}
	}

	//������Ʈ
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			if (tile[y][x].obj == OBJ_BOX1) IMAGEMANAGER->frameRender("�ڽ�1", getMemDC(), tile[y][x].rc.left - 42 - currentCamera.x, tile[y][x].rc.top - 40 - currentCamera.y, 0, 0);
			else if (tile[y][x].obj == OBJ_BOX2_1) IMAGEMANAGER->frameRender("�ڽ�2", getMemDC(), tile[y][x].rc.left - 10 - currentCamera.x, tile[y][x].rc.top - 40 - currentCamera.y, 0, 0);
			else if (tile[y][x].obj == OBJ_ROOT1_1) IMAGEMANAGER->frameRender("��Ʈ1", getMemDC(), tile[y][x].rc.left - 32 - currentCamera.x, tile[y][x].rc.top - 38 - currentCamera.y, 0, 0);
			else if (tile[y][x].obj == OBJ_ROOT2_1) IMAGEMANAGER->frameRender("��Ʈ2", getMemDC(), tile[y][x].rc.left - 32 - currentCamera.x, tile[y][x].rc.top - 38 - currentCamera.y, 0, 0);
		}
	}

	//���ʹ�
	for (int i = 0; i < ENEMYMAX; i++)
	{
		if (m_createEnemy[i].enm == ENM_TURTLE)	IMAGEMANAGER->frameRender("�ź���", getMemDC(), m_createEnemy[i].rc.left - 36 - currentCamera.x, m_createEnemy[i].rc.top - 26 - currentCamera.y, 0, 0);
		else if (m_createEnemy[i].enm == ENM_DUCK) IMAGEMANAGER->frameRender("����", getMemDC(), m_createEnemy[i].rc.left - 38 - currentCamera.x, m_createEnemy[i].rc.top - 30 - currentCamera.y, 0, 0);
		else if (m_createEnemy[i].enm == ENM_KAMIKAZE) IMAGEMANAGER->frameRender("���̰���", getMemDC(), m_createEnemy[i].rc.left - 37 - currentCamera.x, m_createEnemy[i].rc.top - 51 - currentCamera.y, 0, 0);
	}
	
	IMAGEMANAGER->frameRender("����", getMemDC(), Charcter_pt.x - currentCamera.x,  Charcter_pt.y - currentCamera.y);
	testNumber->render(WINSIZEX/2,0, 1);
}

void stageScene::loadStage(char* mapName)
{
	HANDLE file;
	DWORD read;
	file = CreateFile(mapName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	//Ÿ�� �ҷ�����
	ReadFile(file, tile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	//���ʹ� �ҷ�����
	ReadFile(file, m_createEnemy, sizeof(tagCreateEnemy) * ENEMYMAX, &read, NULL);
	CloseHandle(file);
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			if (tile[y][x].terrainFrameY == 0 || (tile[y][x].terrainFrameX >= 15 && tile[y][x].terrainFrameX <= 18) || (tile[y][x].terrainFrameX >= 25 && tile[y][x].terrainFrameX <= 32) || tile[y][x].terrainFrameX >= 39)
			{
				tile[y][x].terrain = TR_WALL;
			}
			if (tile[y][x].terrain == TR_WALL) tile[y][x].attribute = ATTR_UNMOVE;
		}
	}

}
