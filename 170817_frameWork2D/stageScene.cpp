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
	m_bulletManager->loadTile("tileMap1.map");

	m_defaultGun = new defaultGun;

	m_defaultGun->init(CHAR_PLAYER);

	m_cm = new characterManager;
	m_cm->init(Charcter_pt, JIMMY);

	
	m_defaultGun->setBulletManagerLink(*m_bulletManager);

	Charcter_Real_pt = { Charcter_pt.x - currentCamera.x, Charcter_pt.y - currentCamera.y };

		
	testX = 0;
	

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
	

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		m_defaultGun->fire();
	}
	
	//currentCamera = { Charcter_pt.x - 640,Charcter_pt.y - 360 };
	m_cm->update(currentCamera);
	collision_tile_character();
	collision_Object_character();
	Charcter_pt = { (int)m_cm->getPlayerX(),(int)m_cm->getPlayerY() };
	moveCamera(Charcter_pt);
	
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
	//collision_tile_Enemy();
	collision_Object_Enemy();
	m_objectManager->update();
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
				if (tile[y][x].terrain == TR_WALL)Rectangle(getMemDC(), tile[y][x].rc.left - currentCamera.x, tile[y][x].rc.top - currentCamera.y, tile[y][x].rc.right - currentCamera.x, tile[y][x].rc.bottom - currentCamera.y);
				
				
			}
		}
	}

	

	//오브젝트
	m_objectManager->render(currentCamera);
	//총알
	m_bulletManager->render(currentCamera);
	//적
	m_enemyManager->render(currentCamera);
	//캐릭터
	m_cm->render(currentCamera);
	//총
	m_defaultGun->render(currentCamera);
	//숫자
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
							m_cm->setPlayerY(m_cm->getPlayerY()+(temp.bottom-temp.top));
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
	bool collisionTB;
	bool collisionRL;
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
						SetRect(&temp, 0, 0, temp.right - temp.left, temp.bottom - temp.top);
						//상, 하 충돌
						if (temp.bottom < temp.right)
						{
							//위 충돌
							if ((tile[y][x].rc.top + tile[y][x].rc.bottom) / 2 < (enemy_collision_rc.top + enemy_collision_rc.bottom) / 2)
							{
								m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() + (temp.bottom - temp.top));
								
							}
							//아래 충돌
							else
							{
								m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() - (temp.bottom - temp.top));
							
							}
							
						}
						//좌, 우 충돌
						if (temp.bottom >= temp.right)
						{
							//왼쪽 충돌
							if ((tile[y][x].rc.left + tile[y][x].rc.right) / 2 < (enemy_collision_rc.left + enemy_collision_rc.right) / 2)
							{
								m_enemyManager->getVEnemy()[i]->setX(m_enemyManager->getVEnemy()[i]->getX() + (temp.right - temp.left));
								
								
							}
							//오른쪽 충돌
							else
							{
								m_enemyManager->getVEnemy()[i]->setX(m_enemyManager->getVEnemy()[i]->getX() - (temp.right - temp.left));
								
								
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
	RECT tempObject;
	RECT enemy_collision_rc;
	for (int i = 0; i < m_enemyManager->getVEnemy().size(); i++)
	{
		enemy_collision_rc = m_enemyManager->getVEnemy()[i]->getCollisionRect();
		for (int i = 0; i < m_objectManager->getVObject().size(); i++)
		{
			if (m_objectManager->getVObject()[i]->getIsTeleport())continue;

			tempObject = m_objectManager->getVObject()[i]->getRect();
			tempObject = { tempObject.left,tempObject.top - 14,tempObject.right,tempObject.bottom };
			if (IntersectRect(&temp, &enemy_collision_rc, &tempObject))
			{
				//위 충돌
				if ((tempObject.top + tempObject.bottom) / 2 < (enemy_collision_rc.top + enemy_collision_rc.bottom) / 2)
				{
					m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() + 80);
				}
				//아래 충돌
				if ((tempObject.top + tempObject.bottom) / 2 > (enemy_collision_rc.top + enemy_collision_rc.bottom) / 2)
				{
					m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() - 80);
				}
				//왼쪽 충돌
				if ((tempObject.left + tempObject.right) / 2 < (enemy_collision_rc.left + enemy_collision_rc.right) / 2)
				{
					m_enemyManager->getVEnemy()[i]->setX(m_enemyManager->getVEnemy()[i]->getX() + 80);
				}
				//오른쪽 충돌
				if ((tempObject.left + tempObject.right) / 2 > (enemy_collision_rc.left + enemy_collision_rc.right) / 2)
				{
					m_enemyManager->getVEnemy()[i]->setX(m_enemyManager->getVEnemy()[i]->getX() - 80);
				}

				//SetRect(&temp, 0, 0, temp.right - temp.left, temp.bottom - temp.top);
				////상, 하 충돌
				//if (temp.bottom < temp.right)
				//{
				//	//위 충돌
				//	if ((tempObject.top + tempObject.bottom) / 2 < (enemy_collision_rc.top + enemy_collision_rc.bottom) / 2)
				//	{
				//		m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() + (temp.bottom - temp.top));
				//	}
				//	//아래 충돌
				//	else
				//	{
				//		m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() - (temp.bottom - temp.top));
				//	}
				//}
				////좌, 우 충돌
				//else
				//{
				//	//왼쪽 충돌
				//	if ((tempObject.left + tempObject.right) / 2 < (enemy_collision_rc.left + enemy_collision_rc.right) / 2)
				//	{
				//		m_enemyManager->getVEnemy()[i]->setX(m_enemyManager->getVEnemy()[i]->getX() + (temp.right - temp.left));
				//	}
				//	//오른쪽 충돌
				//	else
				//	{
				//		m_enemyManager->getVEnemy()[i]->setX(m_enemyManager->getVEnemy()[i]->getX() - (temp.right - temp.left));
				//	}
				//}
				m_enemyManager->getVEnemy()[i]->setCurrent(STOP_ENEMY);
			}
		}
	}
}

