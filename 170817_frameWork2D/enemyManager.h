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

	//거북이 추가
	void addTurtle(POINT position);
	void addTurtle(POINT position, bulletManager &_bulletManager);



	//오리 추가
	void addDuck(POINT position);
	//가미가제 추가
	void addKamikaze(POINT position);
	//에너미 체력 감소
	void setEnemyHP(int num, int hp);
	//에너미 삭제
	void deleteEnemy();


	vector<enemy*> getVEnemy() { return m_vEnemy; }
	vector<enemy*>::iterator getViEnemy() { return m_viEnemy; }
};
