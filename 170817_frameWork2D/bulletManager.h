#pragma once
#include "bulletInterface.h"
class bulletManager
{
private:
	typedef vector<bulletInterface*> vBulletList;
	typedef vector<bulletInterface*>::iterator viBulletList;
	vector<bulletInterface*> m_vBulletList;//�Ѿ� �������̽��� ���� ����<�Ѿ˺���>
	vector<bulletInterface*>::iterator m_viBulletList;
	int cnt;
public:
	bulletManager();
	~bulletManager();
	HRESULT init();
	void release();
	void update();
	void render();
	void addBullet(bulletInterface &m_bullet);//�Ѿ��� �־��� �Լ�
	void checkBullet();//�Ѿ� �浹üũ
	void deleteBullet(viBulletList &m_bullet);//�Ѿ� �����Լ�
};

