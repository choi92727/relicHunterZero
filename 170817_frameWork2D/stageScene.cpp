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
	testNumber->init("총알숫자", 5);

	currentCamera = { 0,0 };
	Charcter_pt = { WINSIZEX / 2,WINSIZEY / 2 };
	Character_Rc= RectMake(Charcter_pt.x, Charcter_pt.y, 50, 100);
	camera_rc = RectMake(currentCamera.x, currentCamera.y,1280,720);
	speed = 3;

	m_bulletManager = new bulletManager;
	m_bulletManager->init();

	m_defaultGun = new defaultGun;

	m_defaultGun->init(CHAR_PLAYER);
	
	m_defaultGun->setBulletManagerLink(*m_bulletManager);
	Charcter_Real_pt = { Charcter_pt.x - currentCamera.x, Charcter_pt.y - currentCamera.y };
	

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

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		m_defaultGun->fire();
	}

	//currentCamera = { Charcter_pt.x - 640,Charcter_pt.y - 360 };
	moveCamera(Charcter_pt);
	camera_rc = RectMake(currentCamera.x, currentCamera.y, 1280, 720);
	m_defaultGun->setPosition(Charcter_Real_pt.x+IMAGEMANAGER->findImage("지미")->getFrameWidth()/2, Charcter_Real_pt.y+(IMAGEMANAGER->findImage("지미")->getFrameHeight() / 2));

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

	m_defaultGun->update();
	m_bulletManager->update();
}

void stageScene::render()
{
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			if (tileOn[y][x])
			{
				IMAGEMANAGER->frameRender("맵툴", getMemDC(), tile[y][x].rc.left- currentCamera.x, tile[y][x].rc.top - currentCamera.y, tile[y][x].terrainFrameX, tile[y][x].terrainFrameY);
				
				
			}
		}
	}

	//오브젝트
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			if (tile[y][x].obj == OBJ_BOX1) IMAGEMANAGER->frameRender("박스1", getMemDC(), tile[y][x].rc.left - 42 - currentCamera.x, tile[y][x].rc.top - 40 - currentCamera.y, 0, 0);
			else if (tile[y][x].obj == OBJ_BOX2_1) IMAGEMANAGER->frameRender("박스2", getMemDC(), tile[y][x].rc.left - 10 - currentCamera.x, tile[y][x].rc.top - 40 - currentCamera.y, 0, 0);
			else if (tile[y][x].obj == OBJ_ROOT1_1) IMAGEMANAGER->frameRender("루트1", getMemDC(), tile[y][x].rc.left - 32 - currentCamera.x, tile[y][x].rc.top - 38 - currentCamera.y, 0, 0);
			else if (tile[y][x].obj == OBJ_ROOT2_1) IMAGEMANAGER->frameRender("루트2", getMemDC(), tile[y][x].rc.left - 32 - currentCamera.x, tile[y][x].rc.top - 38 - currentCamera.y, 0, 0);
		}
	}

	//에너미
	for (int i = 0; i < ENEMYMAX; i++)
	{
		if (m_createEnemy[i].enm == ENM_TURTLE)	IMAGEMANAGER->frameRender("거북이", getMemDC(), m_createEnemy[i].rc.left - 36 - currentCamera.x, m_createEnemy[i].rc.top - 26 - currentCamera.y, 0, 0);
		else if (m_createEnemy[i].enm == ENM_DUCK) IMAGEMANAGER->frameRender("오리", getMemDC(), m_createEnemy[i].rc.left - 38 - currentCamera.x, m_createEnemy[i].rc.top - 30 - currentCamera.y, 0, 0);
		else if (m_createEnemy[i].enm == ENM_KAMIKAZE) IMAGEMANAGER->frameRender("가미가제", getMemDC(), m_createEnemy[i].rc.left - 37 - currentCamera.x, m_createEnemy[i].rc.top - 51 - currentCamera.y, 0, 0);
	}
	
	IMAGEMANAGER->frameRender("지미", getMemDC(), Charcter_pt.x - currentCamera.x,  Charcter_pt.y - currentCamera.y);
	testNumber->render(WINSIZEX/2,0, 1);

	m_defaultGun->render();
	m_bulletManager->render();
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
	//타일 불러오기
	ReadFile(file, tile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	//에너미 불러오기
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

void stageScene::moveCamera(POINT characterPt)
{
	/*RECT temp=RectMakeCenter (WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);
	if (PtInRect(&temp, ptMouse))
	{
		currentCamera.x = characterPt.x + (ptMouse.x - WINSIZEX / 2) / 4 - WINSIZEX / 2;
		currentCamera.y = characterPt.y + (ptMouse.y - WINSIZEY / 2) / 4 - WINSIZEY / 2;
	}
	temp = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX / 2, WINSIZEY / 2);
	if (PtInRect(&temp, ptMouse))
	{
		currentCamera.x = characterPt.x + (ptMouse.x - WINSIZEX / 2) / 8 - WINSIZEX / 2;
		currentCamera.y = characterPt.y + (ptMouse.y - WINSIZEY / 2) / 8 - WINSIZEY / 2;

	}*/
	
	currentCamera.x = characterPt.x + (ptMouse.x - WINSIZEX / 2) / 8 - WINSIZEX / 2;
	currentCamera.y = characterPt.y + (ptMouse.y - WINSIZEY / 2) / 6 - WINSIZEY / 2;
}
