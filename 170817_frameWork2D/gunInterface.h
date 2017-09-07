#pragma once
#include "gameNode.h"
#include "bulletInterface.h"
#include "bulletManager.h"
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
	CHARACTER m_playerType;//�÷��̾� Ÿ�� ����
	bulletManager* m_bulletManager;//�ҷ��Ŵ��� ����
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
	virtual void setAngle();//�ޱ��� ���� �־��ش�
	virtual void setPosition(int x, int y);//������ �缳��
	float getFireDelay() { return m_fireDelay; }
	void setBulletManagerLink(bulletManager &_bulletManager) { m_bulletManager = &_bulletManager; }
	//�Ѿ� �߻�ø��� �ҷ� �Ŵ������� �־���

};

