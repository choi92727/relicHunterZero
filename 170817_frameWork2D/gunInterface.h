#pragma once
#include "gameNode.h"
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
	Image* m_gunImage;//이미지 회전 시 필요한 변수
	Graphics* m_graphics;//이미지 회전시 필요한 변수
	
public:
	gunInterface();
	virtual ~gunInterface();
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void fire();
	virtual void setAngle();
	virtual void setPosition(int x,int y);
};

