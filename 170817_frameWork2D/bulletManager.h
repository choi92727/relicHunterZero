#pragma once
#include "bulletInterface.h"
class bulletManager
{
private:
	typedef vector<bulletInterface*> vBulletList;
	typedef vector<bulletInterface*>::iterator viBulletList;
	vector<bulletInterface*> m_vBulletList;//총알 인터페이스를 담을 벡터<총알벡터>
	vector<bulletInterface*>::iterator m_viBulletList;
	int cnt;
public:
	bulletManager();
	~bulletManager();
	HRESULT init();
	void release();
	void update();
	void render();
	void addBullet(bulletInterface &m_bullet);//총알을 넣어줄 함수
	void checkBullet();//총알 충돌체크
	void deleteBullet(viBulletList &m_bullet);//총알 제거함수
};

