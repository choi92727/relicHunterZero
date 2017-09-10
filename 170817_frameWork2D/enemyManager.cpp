#include "stdafx.h"
#include "enemyManager.h"
#include "bulletManager.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	addNumber = 1;
	return S_OK;
}

void enemyManager::release()
{
	m_viEnemy = m_vEnemy.begin();
	for (m_viEnemy; m_viEnemy != m_vEnemy.end();)
	{
		m_viEnemy = m_vEnemy.erase(m_viEnemy);
	}
}

void enemyManager::update()
{
	m_viEnemy = m_vEnemy.begin();
	for (m_viEnemy; m_viEnemy != m_vEnemy.end(); m_viEnemy++)
	{
		(*m_viEnemy)->update();
	}
	//if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//{
	//	m_viEnemy = m_vEnemy.begin();
	//	for (m_viEnemy; m_viEnemy != m_vEnemy.end(); m_viEnemy++)
	//	{
	//		(*m_viEnemy)->setHP(10);
	//	}
	//}
	this->deleteEnemy();
}

bool enemyManager::render(POINT pt)
{
	bool isInRect=false;
	RECT temp;
	RECT camera_rc = RectMake(pt.x, pt.y, 1280, 720);
	m_viEnemy = m_vEnemy.begin();
	for (m_viEnemy; m_viEnemy != m_vEnemy.end(); m_viEnemy++)
	{
		if (IntersectRect(&temp, &camera_rc, &(*m_viEnemy)->getRect()))
		{

		(*m_viEnemy)->render(pt);
		isInRect = true;
		}
	}
	return isInRect;
}

//거북이 추가
void enemyManager::addTurtle(POINT position)
{
	turtle* m_turtle;
	m_turtle = new turtle;
	m_turtle->init(position);
	
	m_turtle->setEnemyNumber(addNumber);
	addNumber++;
	m_vEnemy.push_back(m_turtle);
}

void enemyManager::addTurtle(POINT position, bulletManager & _bulletManager)
{
	/*turtle* m_turtle;
	m_turtle = new turtle;
	m_turtle->init(position);
	m_turtle->setisGun(true);
	if (m_turtle->getisGun()) {
		m_turtle->setGun(GUN_DEFAULT);
		m_turtle->setBulletLink(_bulletManager);
	}
	m_vEnemy.push_back(m_turtle);*/

}

//오리 추가
void enemyManager::addDuck(POINT position)
{
	duck* m_duck;
	m_duck = new duck;
	m_duck->init(position);

	m_duck->setEnemyNumber(addNumber);
	addNumber++;
	m_vEnemy.push_back(m_duck);
}

//가미가제 추가
void enemyManager::addKamikaze(POINT position)
{
	kamikaze* m_kamikaze;
	m_kamikaze = new kamikaze;
	m_kamikaze->init(position);

	m_kamikaze->setEnemyNumber(addNumber);
	addNumber++;
	m_vEnemy.push_back(m_kamikaze);
}

//에너미 체력 감소
void enemyManager::setEnemyHP(int num, int hp)
{
	m_viEnemy = m_vEnemy.begin();
	for (m_viEnemy; m_viEnemy != m_vEnemy.end(); m_viEnemy++)
	{
		(*m_viEnemy)->setHP(hp);
	}
}

//에너미 제거
void enemyManager::deleteEnemy()
{
	m_viEnemy = m_vEnemy.begin();
	for (m_viEnemy; m_viEnemy != m_vEnemy.end();)
	{
		if ((*m_viEnemy)->dead()) m_viEnemy = m_vEnemy.erase(m_viEnemy);
		else m_viEnemy++;
	}
}