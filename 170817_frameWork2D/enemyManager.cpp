#include "stdafx.h"
#include "enemyManager.h"


enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	//�׽�Ʈ�� �ź���
	POINT pt1 = { 800, 200 };
	turtle* m_turtle;
	m_turtle = new turtle;
	m_turtle->init(pt1);
	m_vEnemy.push_back(m_turtle);
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
	this->deleteEnemy();
}

void enemyManager::render()
{
	m_viEnemy = m_vEnemy.begin();
	for (m_viEnemy; m_viEnemy != m_vEnemy.end(); m_viEnemy++)
	{
		(*m_viEnemy)->render();
	}
}

//���ʹ� ����
void enemyManager::deleteEnemy()
{
	m_viEnemy = m_vEnemy.begin();
	for (m_viEnemy; m_viEnemy != m_vEnemy.end();)
	{
		if ((*m_viEnemy)->dead()) m_viEnemy = m_vEnemy.erase(m_viEnemy);
		else m_viEnemy++;
	}
}
