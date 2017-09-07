#pragma once
#include "gameNode.h"
#include "bulletInterface.h"
#include "bulletManager.h"
class gunInterface : public gameNode
{
protected:
	float m_damage;//총기 데미지
	float m_speed;//총기속도
	float m_angle;//각도
	float m_x;//가로좌표
	float m_y;//세로좌표
	float m_fireDelay;//총알을 쏘는 제한시간
	float m_isDelay;//실제 도는 제한시간
	bool m_fire;//발사 가능한지 여부
	Image* m_gunImage[2];//이미지 회전 시 필요한 변수
	Graphics* m_graphics;//이미지 회전시 필요한 변수
	CHARACTER m_playerType;//플레이어 타입 변수
	bulletManager* m_bulletManager;//불렛매니저 연동
public:
	bulletInterface* m_bullet;
	gunInterface();
	virtual ~gunInterface();
	virtual HRESULT init(CHARACTER playerType);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(POINT pt);
	virtual void fire();
	virtual void setAngle();//앵글을 새로 넣어준다
	virtual void setPosition(int x, int y);//포지션 재설정
	float getFireDelay() { return m_fireDelay; }
	void setBulletManagerLink(bulletManager &_bulletManager) { m_bulletManager = &_bulletManager; }
	//총알 발사시마다 불렛 매니저에서 넣어줌

};

