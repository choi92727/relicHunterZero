#pragma once
#include "gameNode.h"
#include "bulletInterface.h"
#include "bulletManager.h"
#include "numberDrawManager.h"
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
	GUNTYPE m_gunType;
	numberDrawManager m_currentDraw;
	numberDrawManager m_totalDraw;

	int m_currentBullet;
	int m_maxBullet;
	int m_totalBullet;

	//���ʹ̿� ����
	int m_gunIndex ;
	bool m_enemy_fire = true;
	float m_enemyfireDelay = 1.5f * 60.0f;
	bool m_canFire;



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
	virtual void melee();
	void setAngle(float angle) { m_angle = angle; }//�ޱ��� ���� �־��ش�
	virtual void setPosition(int x, int y);//������ �缳��
	float getFireDelay() { return m_fireDelay; }
	void reload();
	GUNTYPE getGunType() { return m_gunType; }
	void setBulletManagerLink(bulletManager &_bulletManager) { m_bulletManager = &_bulletManager; }
	//�Ѿ� �߻�ø��� �ҷ� �Ŵ������� �־���

	//���ʹ� ����Լ�
	int getGunIndex() { return m_gunIndex; }
	void setGunIndex(int _gunIndex) { m_gunIndex = _gunIndex; }

	bool getEnemyFireTriger() { return m_enemy_fire; }
	void setEnemyFireTriger(bool _bool){ m_enemy_fire = _bool; }

	bool getCanFire() { return m_canFire; }
	void setCanFire(bool _setFire) {m_canFire = _setFire; }



};

