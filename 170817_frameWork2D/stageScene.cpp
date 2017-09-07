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

	m_enemyManager = new enemyManager;
	m_enemyManager->init();
	for (int i = 0; i < ENEMYMAX; i++)
	{
		if (m_createEnemy[i].enm == ENM_TURTLE)	m_enemyManager->addTurtle(m_createEnemy[i].pt);
		else if (m_createEnemy[i].enm == ENM_DUCK) m_enemyManager->addDuck(m_createEnemy[i].pt);
		else if (m_createEnemy[i].enm == ENM_KAMIKAZE)m_enemyManager->addKamikaze(m_createEnemy[i].pt);
		
	}


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

	m_cm = new characterManager;
	m_cm->init(Charcter_pt, JIMMY);

	
	m_defaultGun->setBulletManagerLink(*m_bulletManager);
		
	

	return S_OK;
}

void stageScene::release()
{
	m_cm->release();
	SAFE_DELETE(m_enemyManager);
}

void stageScene::update()
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		Charcter_pt.x-= speed;

	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		Charcter_pt.x += speed;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		Charcter_pt.y -= speed;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		Charcter_pt.y += speed;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		m_defaultGun->fire();
	}
	
	//currentCamera = { Charcter_pt.x - 640,Charcter_pt.y - 360 };
	moveCamera(Charcter_pt);
	Character_Rc = RectMakeCenter(Charcter_pt.x, Charcter_pt.y, 50, 100);
	camera_rc = RectMake(currentCamera.x, currentCamera.y, 1280, 720);
	m_defaultGun->setPosition(Charcter_pt.x - currentCamera.x, Charcter_pt.y - currentCamera.y);
	m_cm->update();
	m_cm->setPlayerX((float)(Charcter_pt.x-currentCamera.x));
	m_cm->setPlayerY((float)(Charcter_pt.y-currentCamera.y));
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
	m_enemyManager->update();
	for (int i = 0; i < m_enemyManager->getVEnemy().size(); i++)
	{
		//플레이어가 에너미 탐지거리에 있으면 트루
		RECT temp;
		if (IntersectRect(&temp, &m_cm->getEnemy_hitRc(), &m_enemyManager->getVEnemy()[i]->getDetectionRect()) && !m_enemyManager->getVEnemy()[i]->getIsDetection()) m_enemyManager->getVEnemy()[i]->setIsDetection(true);

		if (m_enemyManager->getVEnemy()[i]->getCurrent() != DASH_ENEMY && m_enemyManager->getVEnemy()[i]->getIsDetection())
		{
			//에너미 좌우 방향 정하기
			//플레이어가 에너미 왼쪽에 있으면 에너미가 왼쪽으로 보기
			if (m_cm->getPlayerX() < m_enemyManager->getVEnemy()[i]->getX()) m_enemyManager->getVEnemy()[i]->setIsLeft(true);
			//플레이어가 에너미 오른쪽에 있으면 에너미가 오른쪽으로 보기
			else m_enemyManager->getVEnemy()[i]->setIsLeft(false);

			//에너미 앵글 정하기
			m_enemyManager->getVEnemy()[i]->setAngle(getAngle(m_enemyManager->getVEnemy()[i]->getX(), m_enemyManager->getVEnemy()[i]->getY(), m_cm->getPlayerX(), m_cm->getPlayerY()));
		}
	}
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
	
	m_cm->render();
	testNumber->render(WINSIZEX/2,0, 1);

	m_defaultGun->render();
	m_bulletManager->render();
	m_enemyManager->render(currentCamera);
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

void stageScene::loadEnermy(char * mapName)
{
	
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


