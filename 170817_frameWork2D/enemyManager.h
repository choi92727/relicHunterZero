#pragma once
#include "gameNode.h"
#include "enemy.h"


class bulletManager;

class enemyManager : public gameNode
{
private:
	vector<enemy*> m_vEnemy;
	vector<enemy*>::iterator m_viEnemy;
	int addNumber = 1;
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render(POINT pt);

	//�ź��� �߰�
	void addTurtle(POINT position);
	void addTurtle(POINT position, bulletManager &_bulletManager);



	//���� �߰�
	void addDuck(POINT position);
	//���̰��� �߰�
	void addKamikaze(POINT position);
	//���ʹ� ü�� ����
	void setEnemyHP(int num, int hp);
	//���ʹ� ����
	void deleteEnemy();


	vector<enemy*> getVEnemy() { return m_vEnemy; }
	vector<enemy*>::iterator getViEnemy() { return m_viEnemy; }
};
