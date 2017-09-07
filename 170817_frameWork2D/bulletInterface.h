#pragma once
#include "gameNode.h"
class bulletInterface : public gameNode
{

protected:
	float m_speed;
	float m_angle;
	float m_damage;
	float m_range;
	float m_width;//����
	float m_height;//����
	float m_isGravity;
	float m_gravity;
	int m_x, m_y;
	CHARACTER m_playerType;//�Ѿ�Ÿ��
	animation *m_ani;
	image* m_image;//������ ����� imageŬ������ ��ӹ޾Ƽ� ����� �̹���

	Image* m_bulletImage;//drawPng�� ����ϱ� ���� Ŭ���� ���� �빮�ڷ� ������.
	Graphics* m_graphics;//drawPng�� ����ϱ� ���� ����

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
	RECT getRect() {
		return RectMake(m_x, m_y,m_width,m_height / 2);
	}
	
};

