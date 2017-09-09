#pragma once
#include "bulletInterface.h"
#include "tileNode.h"
class bulletManager
{
private:
	typedef vector<bulletInterface*> vBulletList;
	typedef vector<bulletInterface*>::iterator viBulletList;
	vector<bulletInterface*> m_vBulletList;//�Ѿ� �������̽��� ���� ����<�Ѿ˺���>
	vector<bulletInterface*>::iterator m_viBulletList;
	int cnt;
	tagTile m_tagTile[TILEY][TILEX];
public:
	bulletManager();
	~bulletManager();
	HRESULT init();
	void release();
	void update();
	void render();
	void render(POINT pt);
	void addBullet(bulletInterface &m_bullet);//�Ѿ��� �־��� �Լ�
	void bulletMove();
	bool enemyCollisionCheck(RECT &_rc);
	void wallCollsionCheck();
	void deleteBullet(viBulletList &m_bullet);//�Ѿ� �����Լ�s
	void loadTile(char* mapName);
};

