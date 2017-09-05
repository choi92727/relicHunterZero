#pragma once
#include "bulletInterface.h"
#include "gameNode.h"
class bulletManager : public gameNode
{
private:
	typedef vector<bulletInterface*> vBulletList;
	typedef vector<bulletInterface*>::iterator viBulletList;
	vector<bulletInterface*> m_vBulletList;
	vector<bulletInterface*>::iterator m_viBulletList;
	int cnt;
public:
	bulletManager();
	~bulletManager();
	HRESULT init();
	void release();
	void update();
	void render();
	void addBullet(bulletInterface &m_bullet);
	void checkBullet();
};

