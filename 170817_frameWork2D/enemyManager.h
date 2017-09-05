#pragma once
#include "gameNode.h"
#include "enemy.h"

class enemyManager : public gameNode
{
private:
	//���ʹ�
	vector<enemy*> m_vEnemy;
	vector<enemy*>::iterator m_viEnemy;
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void deleteEnemy();
};
