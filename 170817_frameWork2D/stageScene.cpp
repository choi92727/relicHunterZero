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
	loadPlayerAndStage();
	//Ŀ�� ��ο�
	m_cd = new cursorDraw;
	m_cd->init(0);
	
	m_bulletManager = new bulletManager;
	m_bulletManager->init();
	m_bulletManager->loadTile("tileMap1.map");
	m_charcterGetItem = new charcterGetItem;
	m_charcterGetItem->init();
	m_itemManager = new itemManager;
	m_itemManager->init();
	m_enemyManager = new enemyManager;
	m_enemyManager->init();
	for (int i = 0; i < ENEMYMAX; i++)
	{
		if (m_createEnemy[i].enm == ENM_TURTLE)	m_enemyManager->addTurtle(m_createEnemy[i].pt);
		else if (m_createEnemy[i].enm == ENM_DUCK) m_enemyManager->addDuck(m_createEnemy[i].pt);
		else if (m_createEnemy[i].enm == ENM_KAMIKAZE)m_enemyManager->addKamikaze(m_createEnemy[i].pt);

	//	int cnt = RND->getInt(4);

		if (m_createEnemy[i].enm == ENM_KAMIKAZE)
		{
			gunInterface* temp = new noneGun;
			temp->init(CHAR_ENEMY);
			temp->setBulletManagerLink(*m_bulletManager);
			temp->setPosition(m_createEnemy[i].pt.x, m_createEnemy[i].pt.y - 50);

			m_enemyGun.push_back(temp);
		}
		else {
			gunInterface* temp = new plasmaGun;
			temp->init(CHAR_ENEMY);
			temp->setBulletManagerLink(*m_bulletManager);
			temp->setPosition(m_createEnemy[i].pt.x, m_createEnemy[i].pt.y - 50);

			m_enemyGun.push_back(temp);
		}
	}
	testNumber = new numberDrawManager;
	testNumber->init("�Ѿ˼���", 5);

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
	
	player_guns[0]= new defaultGun;
	player_guns[0]->init(CHAR_PLAYER);
	player_guns[0]->setBulletManagerLink(*m_bulletManager);

	player_guns[1] = new machineGun;
	player_guns[1]->init(CHAR_PLAYER);
	player_guns[1]->setBulletManagerLink(*m_bulletManager);

	player_guns[2] = new shotGun;
	player_guns[2]->init(CHAR_PLAYER);
	player_guns[2]->setBulletManagerLink(*m_bulletManager);

	player_guns[3] = new plasmaGun;
	player_guns[3]->init(CHAR_PLAYER);
	player_guns[3]->setBulletManagerLink(*m_bulletManager);


	m_defaultGun = player_guns[0];

	m_defaultGun->init(CHAR_PLAYER);

	m_cm = new characterManager;
	m_cm->init(Charcter_pt, m_stageNode[0].characterName);

	

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
	getIsReload();
	if (m_cm->getMeleeAtk()) {
		m_defaultGun->setAngle(180 * (PI / 180));
	}
	else
	{
		float m_pAngle = getAngle(WINSIZEX / 2, WINSIZEY / 2, ptMouse.x, ptMouse.y);
		m_defaultGun->setAngle(m_pAngle);
	}
	changeWeapon();


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
	m_itemManager->update();
	collision_tile_character();
	collision_Object_character();
	collision_item_detect();
	collision_item_real();
	Charcter_pt = { (int)m_cm->getPlayerX(),(int)m_cm->getPlayerY() };
	m_charcterGetItem->update(m_cm->getPlayerX(), m_cm->getPlayerY());



	
	moveCamera(Charcter_pt);
	Character_Rc = RectMakeCenter(Charcter_pt.x, Charcter_pt.y, 50, 100);
	camera_rc = RectMake(currentCamera.x, currentCamera.y, 1280, 720);

	m_defaultGun->setPosition(Charcter_Real_pt.x+IMAGEMANAGER->findImage("����")->getFrameWidth()/2, Charcter_Real_pt.y+(IMAGEMANAGER->findImage("����")->getFrameHeight() / 2));

	m_defaultGun->setPosition(m_cm->getPlayerX(), m_cm->getPlayerY() - 20);
	
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
	collision_tile_Enemy();
	collision_Object_Enemy();
	m_objectManager->update();
	//enemyDeadCheck();
	dropItem();

	for (int i = 0; i < m_enemyManager->getVEnemy().size(); i++)
	{
		//�÷��̾ ���ʹ� Ž���Ÿ��� ������ Ʈ��
		RECT temp;
		if (IntersectRect(&temp, &m_cm->getEnemy_hitRc(), &m_enemyManager->getVEnemy()[i]->getDetectionRect()) && !m_enemyManager->getVEnemy()[i]->getIsDetection()) m_enemyManager->getVEnemy()[i]->setIsDetection(true);

		if (m_enemyManager->getVEnemy()[i]->getCurrent() != DASH_ENEMY && m_enemyManager->getVEnemy()[i]->getIsDetection())
		{
			//���ʹ� �¿� ���� ���ϱ�
			//�÷��̾ ���ʹ� ���ʿ� ������ ���ʹ̰� �������� ����
			if (m_cm->getPlayerX() < m_enemyManager->getVEnemy()[i]->getX()) m_enemyManager->getVEnemy()[i]->setIsLeft(true);
			//�÷��̾ ���ʹ� �����ʿ� ������ ���ʹ̰� ���������� ����
			else m_enemyManager->getVEnemy()[i]->setIsLeft(false);

			//���ʹ� �ޱ� ���ϱ�
			m_enemyManager->getVEnemy()[i]->setAngle(getAngle(m_enemyManager->getVEnemy()[i]->getX(), m_enemyManager->getVEnemy()[i]->getY(), m_cm->getPlayerX(), m_cm->getPlayerY()));
		}
		m_enemyGun[i]->update();
		m_enemyGun[i]->setPosition(m_enemyManager->getVEnemy()[i]->getX(), m_enemyManager->getVEnemy()[i]->getY() - 10);
		m_enemyGun[i]->setAngle(m_enemyManager->getVEnemy()[i]->getAngle());
	}
	enemyShotGun();
	charMelee();
	if (m_cm->getCompleteTeleport())////////////////////////////////////////////////
	{
		SCENEMANAGER->changeScene("testScene");
	}

}

void stageScene::render()
{
	IMAGEMANAGER->render("���1",getMemDC());
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			if (tileOn[y][x])
			{
				//if (tile[y][x].terrain == TR_WALL)continue;
				IMAGEMANAGER->frameRender("����", getMemDC(), tile[y][x].rc.left- currentCamera.x, tile[y][x].rc.top - currentCamera.y, tile[y][x].terrainFrameX, tile[y][x].terrainFrameY);
				
				
			}
		}
	}

	//������Ʈ
	//for (int y = 0; y < TILEY; y++)
	//{
	//	for (int x = 0; x < TILEX; x++)
	//	{
	//		if (tile[y][x].obj == OBJ_BOX1) IMAGEMANAGER->frameRender("�ڽ�1", getMemDC(), tile[y][x].rc.left - 42 - currentCamera.x, tile[y][x].rc.top - 40 - currentCamera.y, 0, 0);
	//		else if (tile[y][x].obj == OBJ_BOX2_1) IMAGEMANAGER->frameRender("�ڽ�2", getMemDC(), tile[y][x].rc.left - 10 - currentCamera.x, tile[y][x].rc.top - 40 - currentCamera.y, 0, 0);
	//		else if (tile[y][x].obj == OBJ_ROOT1_1) IMAGEMANAGER->frameRender("��Ʈ1", getMemDC(), tile[y][x].rc.left - 32 - currentCamera.x, tile[y][x].rc.top - 38 - currentCamera.y, 0, 0);
	//		else if (tile[y][x].obj == OBJ_ROOT2_1) IMAGEMANAGER->frameRender("��Ʈ2", getMemDC(), tile[y][x].rc.left - 32 - currentCamera.x, tile[y][x].rc.top - 38 - currentCamera.y, 0, 0);
	//	}
	//}

	//���ʹ�
	m_objectManager->render(currentCamera);
	m_itemManager->render(currentCamera);
	m_bulletManager->render(currentCamera);
	if(m_enemyManager->render(currentCamera))
	 enemyGunRender();
	m_cm->render(currentCamera);
	m_defaultGun->render(currentCamera);
	m_charcterGetItem->render(currentCamera);
	testNumber->render(WINSIZEX/2,0, 1);

	
	m_cd->render();
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

void stageScene::getIsReload()
{
	if (m_cd->reload())
	{
		m_defaultGun->reload();
	}
}

void stageScene::changeWeapon()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		m_defaultGun = player_guns[0];
		m_defaultGun->init(CHAR_PLAYER);
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		m_defaultGun = player_guns[1];
		m_defaultGun->init(CHAR_PLAYER);

	}
	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		m_defaultGun = player_guns[2];
	}
	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		m_defaultGun = player_guns[3];
	}
	
}



void stageScene::enemyGunRender()
{
	for (int i = 0; i < m_enemyManager->getVEnemy().size(); i++)
	{
		if (m_enemyGun[i]->getCanFire()) {
			m_enemyGun[i]->render(currentCamera);
		}

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
		if (m_enemyManager->getVEnemy()[i]->getCurrent() == DEAD_ENEMY)
		{
			//m_enemyGun[i]->release();
			m_enemyGun.erase(m_enemyGun.begin() + i);
		}
	}
}

void stageScene::dropItem()
{
	for (int i = 0; i < m_enemyManager->getVEnemy().size(); i++)
	{
		if (m_enemyManager->getVEnemy()[i]->getItemDrop())
		{
			m_enemyManager->getVEnemy()[i]->setItemDrop(false);;
			m_itemManager->addItem(PointMake(m_enemyManager->getVEnemy()[i]->getX(), m_enemyManager->getVEnemy()[i]->getY()));
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
					//��, �� �浹
					if (temp.bottom < temp.right)
					{
						//�� �浹
						if ((tile[y][x].rc.top + tile[y][x].rc.bottom) / 2 < (m_cm->getWall_hitRc().top + m_cm->getWall_hitRc().bottom) / 2)
						{
							m_cm->setPlayerY(m_cm->getPlayerY() + (temp.bottom - temp.top));
						}
						//�Ʒ� �浹
						else
						{
							m_cm->setPlayerY(m_cm->getPlayerY() - (temp.bottom - temp.top));
						}
					}
					//��, �� �浹
					else
					{
						//���� �浹
						if ((tile[y][x].rc.left + tile[y][x].rc.right) / 2 < (m_cm->getWall_hitRc().left + m_cm->getWall_hitRc().right) / 2)
						{
							m_cm->setPlayerX(m_cm->getPlayerX() + (temp.right - temp.left));
						}
						//������ �浹
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
						if (temp.left == enemy_collision_rc.left && temp.right == enemy_collision_rc.right)// ���� �浹
						{

							if (tile_center.y < temp_center.y)//�� �浹
							{
								m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() + (temp.bottom - temp.top));
							}
							//�Ʒ� �浹
							else if (tile_center.y > temp_center.y)
							{
								m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() - (temp.bottom - temp.top));
							}
						}
						else if (temp.top == enemy_collision_rc.top && temp.bottom == enemy_collision_rc.bottom)//�¿� �浹
						{
							//���� �浹
							if (tile_center.x < temp_center.x)
							{
								//m_enemyManager->getVEnemy()[i]->setX(m_enemyManager->getVEnemy()[i]->getX() + (temp.right - temp.left));
								m_enemyManager->getVEnemy()[i]->setX(tile[y][x].rc.right + 21);
							}
							//������ �浹
							else if (tile_center.x > temp_center.x)
							{
								//m_enemyManager->getVEnemy()[i]->setX(m_enemyManager->getVEnemy()[i]->getX() - (temp.right - temp.left));
								m_enemyManager->getVEnemy()[i]->setX(tile[y][x].rc.left - 21);
							}
						}
						else//�밢�� �浹
						{
							if (temp_center.x > tile_center.x)//�����浹
							{
								if (temp_center.y > tile_center.y)//���浹
								{
									m_enemyManager->getVEnemy()[i]->setX(m_enemyManager->getVEnemy()[i]->getX() + (temp.right - temp.left));
									m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() + (temp.bottom - temp.top));
								}
								else//�Ʒ� �浹
								{
									m_enemyManager->getVEnemy()[i]->setX(m_enemyManager->getVEnemy()[i]->getX() + (temp.right - temp.left));
									m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() - (temp.bottom - temp.top));
								}

							}
							else//������ �浹
							{
								if (temp_center.y > tile_center.y)
								{
									m_enemyManager->getVEnemy()[i]->setX(m_enemyManager->getVEnemy()[i]->getX() - (temp.right - temp.left));
									m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() + (temp.bottom - temp.top));
								}
								else
								{
									m_enemyManager->getVEnemy()[i]->setX(m_enemyManager->getVEnemy()[i]->getX() - (temp.right - temp.left));
									m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() - (temp.bottom - temp.top));
								}
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

		tempObject = m_objectManager->getVObject()[i]->getRect();
		tempObject = { tempObject.left,tempObject.top - 14,tempObject.right,tempObject.bottom };
		if (m_objectManager->getVObject()[i]->getIsTeleport())
		{
			if (IntersectRect(&temp, &m_cm->getWall_hitRc(), &tempObject))
			{
				m_charcterGetItem->canGet(true);
			}
			else
			{
				m_charcterGetItem->canGet(false);
			}
		}
		else {
			if (IntersectRect(&temp, &m_cm->getWall_hitRc(), &tempObject))
			{
				SetRect(&temp, 0, 0, temp.right - temp.left, temp.bottom - temp.top);
				//��, �� �浹
				if (temp.bottom < temp.right)
				{
					//�� �浹
					if ((tempObject.top + tempObject.bottom) / 2 < (m_cm->getWall_hitRc().top + m_cm->getWall_hitRc().bottom) / 2)
					{
						m_cm->setPlayerY(m_cm->getPlayerY() + (temp.bottom - temp.top));
					}
					//�Ʒ� �浹
					else
					{
						m_cm->setPlayerY(m_cm->getPlayerY() - (temp.bottom - temp.top));
					}
				}
				//��, �� �浹
				else
				{
					//���� �浹
					if ((tempObject.left + tempObject.right) / 2 < (m_cm->getWall_hitRc().left + m_cm->getWall_hitRc().right) / 2)
					{
						m_cm->setPlayerX(m_cm->getPlayerX() + (temp.right - temp.left));
					}
					//������ �浹
					else
					{
						m_cm->setPlayerX(m_cm->getPlayerX() - (temp.right - temp.left));
					}
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
					if (temp.left == enemy_collision_rc.left && temp.right == enemy_collision_rc.right)// ���� �浹
					{

						if (object_center.y < temp_center.y)//�� �浹
						{
							m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() + (temp.bottom - temp.top));
						}
						//�Ʒ� �浹
						else if (object_center.y > temp_center.y)
						{
							m_enemyManager->getVEnemy()[i]->setY(m_enemyManager->getVEnemy()[i]->getY() - (temp.bottom - temp.top));
						}
					}
					else if (temp.top == enemy_collision_rc.top && temp.bottom == enemy_collision_rc.bottom)//�¿� �浹
					{
						//���� �浹
						if (object_center.x < temp_center.x)
						{
							m_enemyManager->getVEnemy()[i]->setX(object_colision_rc.right + 21);
						}
						//������ �浹
						else if (object_center.x > temp_center.x)
						{
							m_enemyManager->getVEnemy()[i]->setX(object_colision_rc.left - 21);
						}
					}
					else//�밢�� �浹
					{
						
					}
					m_enemyManager->getVEnemy()[i]->setCurrent(STOP_ENEMY);
				}
			}
		}
	}
}

void stageScene::collision_item_detect()
{
	RECT tempRC;
	for (int i = 0; i < m_itemManager->getVEnemy().size(); i++)
	{
		if (IntersectRect(&tempRC, &m_itemManager->getVEnemy()[i]->getDetectRc(), &m_cm->getEnemy_hitRc()))
		{
			m_itemManager->getVEnemy()[i]->setX(m_itemManager->getVEnemy()[i]->getX() - (m_itemManager->getVEnemy()[i]->getX() - m_cm->getPlayerX()) / 20);
			m_itemManager->getVEnemy()[i]->setY(m_itemManager->getVEnemy()[i]->getY() - (m_itemManager->getVEnemy()[i]->getY() - m_cm->getPlayerY()) / 20);
		}
	}
}

void stageScene::collision_item_real()
{
	RECT tempRC;
	for (int i = 0; i < m_itemManager->getVEnemy().size(); i++)
	{
		if (IntersectRect(&tempRC, &m_itemManager->getVEnemy()[i]->getRealRc(), &m_cm->getEnemy_hitRc()))//������ �Ծ�����

		{
			
			switch (m_itemManager->getVEnemy()[i]->getType())
			{
			case AMMO0:
				m_defaultGun->setTotalBullet(10);
				break;
			case AMMO1:
				m_defaultGun->setTotalBullet(10);
				break;
			case AMMO2:
				m_defaultGun->setTotalBullet(10);
				break;
			case HEALTH:
				m_cm->setCurrentHP(m_cm->getCurrentHP() + 10);
				if(m_cm->getCurrentHP())
				break;

			
			}
			m_itemManager->getVEnemy()[i]->setPick();
		}
	}
}


void stageScene::stageClear()
{
	HANDLE file;
	DWORD write;

	if (m_stageNode[0].stage == 0) m_stageNode[0].stage = 1;
	else if (m_stageNode[0].stage == 1) m_stageNode[0].stage = 2;
	else if (m_stageNode[0].stage == 2) m_stageNode[0].stage = 3;

	m_stageNode[0].HP = m_cm->getCurrentHP();
	m_stageNode[0].currentBullet;
	m_stageNode[0].maxBullet = 10;

	file = CreateFile("stageNode.stage",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	WriteFile(file, m_stageNode, sizeof(tagStageNode), &write, NULL);
	CloseHandle(file);
}

void stageScene::loadPlayerAndStage()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("stageNode.stage",
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	ReadFile(file, m_stageNode, sizeof(tagStageNode), &read, NULL);
	CloseHandle(file);

	if (m_stageNode[0].stage == 0)
	{
		loadStage("tileMap1.map");
		SOUNDMANAGER->play("���ּ�");
	}
	else if (m_stageNode[0].stage == 1)
	{
		loadStage("tileMap2.map");
		SOUNDMANAGER->play("��������1",0.2f);
	}
	else if (m_stageNode[0].stage == 2)
	{
		loadStage("tileMap3.map");
		SOUNDMANAGER->play("��������2", 0.2f);
	}
	else if (m_stageNode[0].stage == 3)
	{
		loadStage("tileMap4.map");
		SOUNDMANAGER->play("��������3", 0.2f);
	}
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
	ReadFile(file, m_createObject, sizeof(tagCreateObject) * OBJECTMAX, &read, NULL);
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
			else tile[y][x].attribute = ATTR_POSITION;
		}
	}

}