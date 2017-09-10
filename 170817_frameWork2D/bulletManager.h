#pragma once
#include "bulletInterface.h"
#include "defaultBullet.h"
#include "machineBullet.h"
#include "shotBullet.h"
#include "plasmarBullet.h"
#include "enemyManager.h"
#include "tileNode.h"
#include "objectManager.h"
#include "characterManager.h"
#include "collisionBullet.h"

#include "gameNode.h"
class bulletManager : public gameNode
{
private:
	typedef vector<bulletInterface*> vBulletList;
	typedef vector<bulletInterface*>::iterator viBulletList;
	vector<bulletInterface*> m_vBulletList;//�Ѿ� �������̽��� ���� ����<�Ѿ˺���>
	vector<bulletInterface*>::iterator m_viBulletList;
	int cnt;
	tagTile m_tagTile[TILEY][TILEX];
	enemyManager *m_enemyManager;
	objectManager *m_objectManager;
	characterManager* m_character;

public:
	bulletManager();
	~bulletManager();
	HRESULT init();
	void release();
	void update();
	void render();
	void render(POINT pt);
	void addBullet(GUNTYPE _gunType,int x,int y,float angle,float speed,CHARACTER playerType);//�Ѿ��� �־��� �Լ�
	void addCollisionBullet(CHARACTER _char, RECT rc, float damage, float angle, float speed, float range);
	void bulletMove();
	void enemyCollisionCheck();
	void objectCollisionCheck();
	void CharCollisionCheck();
	void wallCollsionCheck();
	void deleteBullet(viBulletList &m_bullet);//�Ѿ� �����Լ�s
	void loadTile(char* mapName);
	void setEnemyLink(enemyManager &_enemyManager) { m_enemyManager = &_enemyManager; }
	void setObjectLink(objectManager &_objectManager) { m_objectManager = &_objectManager; }
	void setCharLink(characterManager &_char) { m_character = &_char; }


};

