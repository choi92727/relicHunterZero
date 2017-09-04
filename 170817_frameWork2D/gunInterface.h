#pragma once
#include "gameNode.h"
class gunInterface : public gameNode
{
protected:
	float m_damage;//�ѱ� ������
	float m_speed;//�ѱ�ӵ�
	float m_angle;//����
	float m_x;//������ǥ
	float m_y;//������ǥ
	float m_fireDelay;//�Ѿ��� ��� ���ѽð�
	float m_isDelay;//���� ���� ���ѽð�
	bool m_fire;//�߻� �������� ����
	Image* m_gunImage[2];//�̹��� ȸ�� �� �ʿ��� ����
	Graphics* m_graphics;//�̹��� ȸ���� �ʿ��� ����
	CHARACTER m_playerType;
	
public:
	gunInterface();
	virtual ~gunInterface();
	virtual HRESULT init(CHARACTER playerType);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void fire();
	virtual void setAngle();
	virtual void setPosition(int x,int y);
};
