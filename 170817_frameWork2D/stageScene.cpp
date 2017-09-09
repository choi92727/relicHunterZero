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

	m_bulletManager = new bulletManager;
	m_bulletManager->init();
	m_bulletManager->loadTile("tileMap1.map");


	m_enemyManager = new enemyManager;
	m_enemyManager->init();
	for (int i = 0; i < ENEMYMAX; i++)
	{
		if (m_createEnemy[i].enm == ENM_TURTLE)	m_enemyManager->addTurtle(m_createEnemy[i].pt);
		else if (m_createEnemy[i].enm == ENM_DUCK) m_enemyManager->addDuck(m_createEnemy[i].pt);
		else if (m_createEnemy[i].enm == ENM_KAMIKAZE)m_enemyManager->addKamikaze(m_createEnemy[i].pt);


		if (m_createEnemy[i].enm != ENM_KAMIKAZE) {
			gunInterface* temp = new defaultGun;
			temp->init(CHAR_ENEMY);
			temp->setBulletManagerLink(*m_bulletManager);
			temp->setPosition(m_createEnemy[i].pt.x, m_createEnemy[i].pt.y - 50);

			m_enemyGun.push_back(temp);
		}
	}


	testNumber = new numberDrawManager;
	testNumber->init("총알숫자", 5);

	currentCamera = { 0,0 };
	Charcter_pt = { WINSIZEX / 2,WINSIZEY / 2 };
	Character_Rc= RectMake(Charcter_pt.x, Charcter_pt.y, 50, 100);
	camera_rc = RectMake(currentCamera.x, currentCamera.y,1280,720);
	speed = 3;

	
	m_bulletManager->setEnemyLink(*m_enemyManager);

	m_objectManager = new objectManager;
	m_objectManager->init();
	for (int i = 0; i < OBJECTMAX; i++)
	{
		if (m_createObject[i].obj == OBJ_BOX1)	m_objectManager->addBox1(m_createObject[i].pt);
		else if (m_createObject[i].obj == OBJ_BOX2) m_objectManager->addBox2(m_createObject[i].pt);
		else if (m_createObject[i].obj == OBJ_ROOT1)m_objectManager->addRoot1(m_createObject[i].pt);
		else if (m_createObject[i].obj == OBJ_ROOT2)m_objectManager->addRoot2(m_createObject[i].pt);
		else if (m_createObject[i].obj == OBJ_TELEPORT)m_objectManager->addTeleport(m_createObject[i].pt);

	}
	m_bulletManager->setObjectLink(*m_objectManager);
	m_defaultGun = new defaultGun;

	m_defaultGun->init(CHAR_PLAYER);

	m_cm = new characterManager;
	m_cm->init(Charcter_pt, JIMMY);

	
	m_defaultGun->setBulletManagerLink(*m_bulletManager);

	Charcter_Real_pt = { Charcter_pt.x - currentCamera.x, Charcter_pt.y - currentCamera.y };

		
	testX = 0;
	
	m_bulletManager->setCharLink(*m_cm);
	return S_OK;
}

void stageScene::release()
{
	m_cm->release();
	//m_enemyManager->release();
	SAFE_DELETE(m_enemyManager);
	//m_objectManager->release();
	SAFE_DELETE(m_objectManager);
}

void stageScene::update()
{
	float m_pAngle = getAngle(WINSIZEX / 2, WINSIZEY / 2, ptMouse.x, ptMouse.y);
	m_defaultGun->setAngle(m_pAngle);


	/*if (KEYMANAGER->isStayKeyDown('A'))
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
	}*/

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		m_defaultGun->fire();
	}
	
	//currentCamera = { Charcter_pt.x - 640,Charcter_pt.y - 360 };
	m_cm->update(currentCamera);
	collision_tile_character();
	Charcter_pt = { (int)m_cm->getPlayerX(),(int)m_cm->getPlayerY() };
	moveCamera(Charcter_pt);
	Character_Rc = RectMakeCenter(Charcter_pt.x, Charcter_pt.y, 50, 100);
	camera_rc = RectMake(currentCamera.x, currentCamera.y, 1280, 720);

	m_defaultGun->setPosition(Charcter_Real_pt.x+IMAGEMANAGER->findImage("지미")->getFrameWidth()/2, Charcter_Real_pt.y+(IMAGEMANAGER->findImage("지미")->getFrameHeight() / 2));

	m_defaultGun->setPosition(m_cm->getPlayerX(), m_cm->getPlayerY());
	
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
	testNumber->update(testX);

	m_defaultGun->update();
	m_bulletManager->update();
	m_enemyManager->update();
	m_objectManager->update();
	enemyDeadCheck();

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
		m_enemyGun[i]->update();
		m_enemyGun[i]->setPosition(m_enemyManager->getVEnemy()[i]->getX(), m_enemyManager->getVEnemy()[i]->getY() - 10);
		m_enemyGun[i]->setAngle(m_enemyManager->getVEnemy()[i]->getAngle());
	}
	enemyShotGun();
}

void stageScene::render()
{
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			if (tileOn[y][x])
			{
				//if (tile[y][x].terrain == TR_WALL)continue;
				IMAGEMANAGER->frameRender("맵툴", getMemDC(), tile[y][x].rc.left- currentCamera.x, tile[y][x].rc.top - currentCamera.y, tile[y][x].terrainFrameX, tile[y][x].terrainFrameY);
				
				
			}
		}
	}

	//오브젝트
	//for (int y = 0; y < TILEY; y++)
	//{
	//	for (int x = 0; x < TILEX; x++)
	//	{
	//		if (tile[y][x].obj == OBJ_BOX1) IMAGEMANAGER->frameRender("박스1", getMemDC(), tile[y][x].rc.left - 42 - currentCamera.x, tile[y][x].rc.top - 40 - currentCamera.y, 0, 0);
	//		else if (tile[y][x].obj == OBJ_BOX2_1) IMAGEMANAGER->frameRender("박스2", getMemDC(), tile[y][x].rc.left - 10 - currentCamera.x, tile[y][x].rc.top - 40 - currentCamera.y, 0, 0);
	//		else if (tile[y][x].obj == OBJ_ROOT1_1) IMAGEMANAGER->frameRender("루트1", getMemDC(), tile[y][x].rc.left - 32 - currentCamera.x, tile[y][x].rc.top - 38 - currentCamera.y, 0, 0);
	//		else if (tile[y][x].obj == OBJ_ROOT2_1) IMAGEMANAGER->frameRender("루트2", getMemDC(), tile[y][x].rc.left - 32 - currentCamera.x, tile[y][x].rc.top - 38 - currentCamera.y, 0, 0);
	//	}
	//}

	//에너미
	m_objectManager->render(currentCamera);
	m_bulletManager->render(currentCamera);
	m_enemyManager->render(currentCamera);
	enemyGunRender();
	m_cm->render(currentCamera);
	m_defaultGun->render(currentCamera);
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
	//타일 불러오기
	ReadFile(file, tile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	//오브젝트 불러오기
	ReadFile(file, m_createObject, sizeof(tagCreateObject) * OBJECTMAX, &read, NULL);
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
			else tile[y][x].attribute = ATTR_POSITION;
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



void stageScene::enemyGunRender()
{
	for (auto i = m_enemyGun.begin(); i != m_enemyGun.end(); i++)
	{
		(*i)->render(currentCamera);
	}
}

void stageScene::enemyShotGun()
{
	for (int i = 0; i < m_enemyManager->getVEnemy().size(); i++)
	{
		if (m_enemyManager->getVEnemy()[i]->getIsDetection() && m_enemyGun[i]->getEnemyFireTriger())
		{
			m_enemyGun[i]->setEnemyFireTriger(false);
			m_enemyGun[i]->fire();
		}
	}
}

void stageScene::enemyDeadCheck()
{
	for (int i = 0; i < m_enemyManager->getVEnemy().size(); i++)
	{
		if (m_enemyManager->getVEnemy()[i]->getCurrent() == DEAD_ENEMY && m_enemyManager->getVEnemy()[i]->getFireEnemy())
		{
			//m_enemyGun[i]->release();
			m_enemyGun.erase(m_enemyGun.begin() + i);
		}
	}
}

void stageScene::collision_tile_character()
{
	RECT temp;

	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			if (IntersectRect(&temp, &m_cm->getWall_hitRc(), &tile[y][x].rc))
			{

				if (tile[y][x].attribute == ATTR_UNMOVE)
				{
					SetRect(&temp, 0, 0, temp.right - temp.left, temp.bottom - temp.top);
					//상, 하 충돌
					if (temp.bottom < temp.right)
					{
						//위 충돌
						if ((tile[y][x].rc.top + tile[y][x].rc.bottom) / 2 < (m_cm->getWall_hitRc().top + m_cm->getWall_hitRc().bottom) / 2)
						{
							m_cm->setPlayerY(m_cm->getPlayerY() + (temp.bottom - temp.top));
						}
						//아래 충돌
						else
						{
							m_cm->setPlayerY(m_cm->getPlayerY() - (temp.bottom - temp.top));
						}
					}
					//좌, 우 충돌
					else
					{
						//왼쪽 충돌
						if ((tile[y][x].rc.left + tile[y][x].rc.right) / 2 < (m_cm->getWall_hitRc().left + m_cm->getWall_hitRc().right) / 2)
						{
							m_cm->setPlayerX(m_cm->getPlayerX() + (temp.right - temp.left));
						}
						//오른쪽 충돌
						else
						{
							m_cm->setPlayerX(m_cm->getPlayerX() - (temp.right - temp.left));
						}
					}
				}
			}
		}
	}
}

void stageScene::collision_tile_Enemy()
{
	RECT temp;
	RECT enemy_collision_rc;
	for (int i = 0; i < m_enemyManager->getVEnemy().size(); i++)
	{
		enemy_collision_rc = m_enemyManager->getVEnemy()[i]->getCollisionRect();

		for (int y = 0; y < TILEY; y++)
		{
			for (int x = 0; x < TILEX; x++)
			{
				if (IntersectRect(&temp, &enemy_collision_rc, &tile[y][x].rc))
				{
					if (tile[y][x].attribute == ATTR_UNMOVE)
					{
						POINT temp_center = { temp.left + (temp.right - temp.left) / 2,temp.top + (temp.bottom - temp.top) / 2 };
						POINT tile_center = { tile[y][x].rc.left + (tile[y][x].rc.right - tile[y][x].rc.left) / 2,tile[y][x].rc.top + (tile[y][x].rc.bottom - tile[y][x].rc.top) / 2 };
						if (temp.left == enemy_collision_rc.left && temp.right == enemy_collision_rc.right)// 상하 충돌
						{

							if (tile_center.y < temp_center.y)//위 충돌
							{
								m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() + (temp.bottom - temp.top));
							}
							//아래 충돌
							else if (tile_center.y > temp_center.y)
							{
								m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() - (temp.bottom - temp.top));
							}
						}
						else if (temp.top == enemy_collision_rc.top && temp.bottom == enemy_collision_rc.bottom)//좌우 충돌
						{
							//왼쪽 충돌
							if (tile_center.x < temp_center.x)
							{
								//m_enemyManager->getVEnemy()[i]->setX(m_enemyManager->getVEnemy()[i]->getX() + (temp.right - temp.left));
								m_enemyManager->getVEnemy()[i]->setX(tile[y][x].rc.right + 21);
							}
							//오른쪽 충돌
							else if (tile_center.x > temp_center.x)
							{
								//m_enemyManager->getVEnemy()[i]->setX(m_enemyManager->getVEnemy()[i]->getX() - (temp.right - temp.left));
								m_enemyManager->getVEnemy()[i]->setX(tile[y][x].rc.left - 21);
							}
						}
						m_enemyManager->getVEnemy()[i]->setCurrent(STOP_ENEMY);
					}
				}
			}
		}
	}
}


void stageScene::collision_Object_character()
{
	RECT temp;
	RECT tempObject;

	for (int i = 0; i < m_objectManager->getVObject().size(); i++)
	{
		if (m_objectManager->getVObject()[i]->getIsTeleport())continue;

		tempObject = m_objectManager->getVObject()[i]->getRect();
		tempObject = { tempObject.left,tempObject.top - 14,tempObject.right,tempObject.bottom };
		if (IntersectRect(&temp, &m_cm->getWall_hitRc(), &tempObject))
		{
			SetRect(&temp, 0, 0, temp.right - temp.left, temp.bottom - temp.top);
			//상, 하 충돌
			if (temp.bottom < temp.right)
			{
				//위 충돌
				if ((tempObject.top + tempObject.bottom) / 2 < (m_cm->getWall_hitRc().top + m_cm->getWall_hitRc().bottom) / 2)
				{
					m_cm->setPlayerY(m_cm->getPlayerY() + (temp.bottom - temp.top));
				}
				//아래 충돌
				else
				{
					m_cm->setPlayerY(m_cm->getPlayerY() - (temp.bottom - temp.top));
				}
			}
			//좌, 우 충돌
			else
			{
				//왼쪽 충돌
				if ((tempObject.left + tempObject.right) / 2 < (m_cm->getWall_hitRc().left + m_cm->getWall_hitRc().right) / 2)
				{
					m_cm->setPlayerX(m_cm->getPlayerX() + (temp.right - temp.left));
				}
				//오른쪽 충돌
				else
				{
					m_cm->setPlayerX(m_cm->getPlayerX() - (temp.right - temp.left));
				}
			}

		}
	}
}

void stageScene::collision_Object_Enemy()
{
	RECT temp;
	RECT enemy_collision_rc;
	RECT object_colision_rc;
	for (int i = 0; i < m_enemyManager->getVEnemy().size(); i++)
	{
		for (int j = 0; j < m_objectManager->getVObject().size(); j++)
		{
			enemy_collision_rc = m_enemyManager->getVEnemy()[i]->getCollisionRect();
			object_colision_rc = m_objectManager->getVObject()[j]->getRect();
			if (IntersectRect(&temp, &enemy_collision_rc, &object_colision_rc))
			{
				if (!m_objectManager->getVObject()[j]->getIsTeleport())
				{
					POINT temp_center = { temp.left + (temp.right - temp.left) / 2,temp.top + (temp.bottom - temp.top) / 2 };
					POINT object_center = { object_colision_rc.left + (object_colision_rc.right - object_colision_rc.left) / 2, object_colision_rc.top + (object_colision_rc.bottom - object_colision_rc.top) / 2 };
					if (temp.left == enemy_collision_rc.left && temp.right == enemy_collision_rc.right)// 상하 충돌
					{

						if (object_center.y < temp_center.y)//위 충돌
						{
							m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() + (temp.bottom - temp.top));
						}
						//아래 충돌
						else if (object_center.y > temp_center.y)
						{
							m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() - (temp.bottom - temp.top));
						}
					}
					else if (temp.top == enemy_collision_rc.top && temp.bottom == enemy_collision_rc.bottom)//좌우 충돌
					{
						//왼쪽 충돌
						if (object_center.x < temp_center.x)
						{
							m_enemyManager->getVEnemy()[i]->setX(object_colision_rc.right + 21);
						}
						//오른쪽 충돌
						else if (object_center.x > temp_center.x)
						{
							m_enemyManager->getVEnemy()[i]->setX(object_colision_rc.left - 21);
						}
					}
					m_enemyManager->getVEnemy()[i]->setCurrent(STOP_ENEMY);
				}
			}
		}
	}
}



