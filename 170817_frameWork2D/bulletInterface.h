#pragma once
#include "gameNode.h"
class bulletInterface : public gameNode
{

protected:
	float m_speed;
	float m_angle;
	float m_damage;
	float m_range;
	float m_width;
	float m_height;
	float m_isGravity;
	float m_gravity;
	int m_x, m_y;
	CHARACTER m_playerType;//총알타입
	animation *m_ani;
	image* m_image;//수업떄 배웠던 image클래스를 상속받아서 만드는 이미지

	Image* m_bulletImage;//drawPng를 사용하기 위한 클래스 위에 대문자로 시작함.
	Graphics* m_graphics;

public:	
	bulletInterface();
	~bulletInterface();
	virtual void fire(int x,int y,float angle,float speed,CHARACTER playerType);
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	float getDamage() { return m_damage; }
	float getRange() { return m_range; }
	float getWidth() { return m_width; }
	float getHeight() { return m_height; }
	CHARACTER getPlayerType() { return m_playerType; }
	int getX() { return m_x; }
	int getY() { return m_y; }

	
};

