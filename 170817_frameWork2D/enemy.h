#pragma once
#include "gameNode.h"
#include "progressBar.h"

class gunInterface;


//���ʹ� ���� ����
enum currentEnemy
{
	STOP_ENEMY,		//(����) ����
	MOVE_ENEMY,		//(�̵�) ����
	HIT_ENEMY,		//(�ǰ�) ����
	DEAD_ENEMY,		//(����) ����
	DASH_ENEMY,		//(�뽬) ����, ���̰��� ����
};


//���ʹ� ����ü
struct tagEnemy
{
	image* image;
	RECT rc;
	RECT detectionRc;
	float x, y;
	int currentHP, maxHP;
	float speed;
	float angle;
	float walkAngle;
	int walkDistance;
	int walkCoolTime, walkCoolTimeMax;
	float dashAngle;                  //����, ���̰��� ����
	int dashCoolTime, dashCoolTimeMax;      //����, ���̰��� ����
	float dash, acceleration;            //����, ���̰��� ����
	int count, detectionCount;
	int currentFrameX, currentFrameY;
	int detectionX;
	bool isDetection, detection;
	bool isLeft;
	bool itemDrop;
	currentEnemy current;
	RECT collisionRc;
	//�Ѿ� �߻� ����
	bool fire = true;
	float fireDelay= 1.5f * 60.0f;//�Ѿ� �߻� ���ð�
	bool fireEnemy = false;//���� ��� ���ʹ�����
	int enemyNumber = 0;//���� ���ʹ��� ���ڰ�
	ENEMY_TYPE m_enemyType;
};

class enemy :public gameNode
{
private:
	tagEnemy m_enemy;
	progressBar* m_progressBar;
public:
	enemy();
	virtual ~enemy();

	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render(POINT pt);

	virtual void detection();
	virtual void animation();
	virtual void dashCoolTime();
	virtual bool dead();
	virtual bool dash();
	virtual void walkCoolTime();
	virtual void walk();
	//���ʹ� ��ü ��Ʈ
	virtual RECT getRect() { return m_enemy.rc; }

	//���ʹ� Ž���Ÿ� ��Ʈ
	virtual RECT getDetectionRect() { return m_enemy.detectionRc; }
	virtual RECT getCollisionRect() { return m_enemy.collisionRc; }
	

	//���ʹ� X
	virtual float getX() { return m_enemy.x; }
	virtual void setX(float x) { m_enemy.x = x; }

	//���ʹ� Y
	virtual float getY() { return m_enemy.y; }
	virtual void setY(float y) { m_enemy.y = y; }

	//���ʹ� �ޱ�
	virtual float getAngle() { return m_enemy.angle; }
	virtual void setAngle(float angle) { m_enemy.angle = angle; }

	//������ �߰��� �Լ�
	 bool getFire() { return m_enemy.fire; }
	 void setFire(bool _fire) { m_enemy.fire = _fire; }
	 float getFireDelay() { return m_enemy.fireDelay; }
	 void setFireDelay(float _delay) { m_enemy.fireDelay = _delay; }
	
	 int getEnemyNumber() { return m_enemy.enemyNumber; }
	 void setEnemyNumber(int _number) { m_enemy.enemyNumber = _number; }

	 bool getFireEnemy() { return m_enemy.fireEnemy; }
	 virtual bool fireCheck();

	 ENEMY_TYPE getEnemyType() { return m_enemy.m_enemyType; }




	//���ʹ� ���� ü�� ����
	virtual void setHP(int hp)
	{
		if (m_enemy.current != DEAD_ENEMY)
		{
			m_enemy.currentHP -= hp;
			m_enemy.count = 0;
			m_enemy.currentFrameX = 0;
			//���� ü���� ���� ��� ���� ��� �ߵ�
			if (m_enemy.currentHP <= 0)
			{
				m_enemy.current = DEAD_ENEMY;
				m_enemy.itemDrop = true;
			}
			//���� ü���� �������� ��� �ǰ� ��� �ߵ�
			else m_enemy.current = HIT_ENEMY;
		}
	}

	//���ʹ� ���� ü�� ����
	virtual void setHP1(int hp) { m_enemy.currentHP = hp; }

	//���ʹ� Ž���߳�?
	virtual bool getIsDetection() { return m_enemy.isDetection; }
	virtual void setIsDetection(bool isDetection) { m_enemy.isDetection = isDetection; }

	//���ʹ� ������ ���� �ֳ�?
	virtual void setIsLeft(bool isLeft) { m_enemy.isLeft = isLeft; }

	//���ʹ� ���� ����
	virtual currentEnemy getCurrent() { return m_enemy.current; }
	virtual void setCurrent(currentEnemy current)
	{
		m_enemy.current = current;
		m_enemy.count = m_enemy.currentFrameX = 0;
	}

	virtual bool getItemDrop() { return false; }
	virtual void setItemDrop(bool itemDrop) {}
};

//�ź��� Ŭ����
class turtle : public enemy
{
private:
	tagEnemy m_enemy;
	progressBar* m_progressBar;
public:
	turtle();
	~turtle();

	HRESULT init(POINT position);
	void release();
	void update();
	void render(POINT pt);

	void detection();
	void animation();
	bool dead();
	void walkCoolTime();
	void walk();
	//���ʹ� ��ü ��Ʈ
	RECT getRect() { return m_enemy.rc; }

	//���ʹ� Ž���Ÿ� ��Ʈ
	RECT getDetectionRect() { return m_enemy.detectionRc; }

	RECT getCollisionRect() { return m_enemy.collisionRc; }
	//���ʹ� X
	float getX() { return m_enemy.x; }
	void setX(float x) { m_enemy.x = x; }

	//���ʹ� Y
	float getY() { return m_enemy.y; }
	void setY(float y) { m_enemy.y = y; }

	//���ʹ� �ޱ�
	float getAngle() { return m_enemy.angle; }
	void setAngle(float angle) { m_enemy.angle = angle; }

	//���ʹ� ���� ü�� ����
	void setHP(int hp)
	{
		if (m_enemy.current != DEAD_ENEMY)
		{
			m_enemy.currentHP -= hp;
			m_enemy.count = 0;
			m_enemy.currentFrameX = 0;
			//���� ü���� ���� ��� ���� ��� �ߵ�
			if (m_enemy.currentHP <= 0)
			{
				m_enemy.current = DEAD_ENEMY;
				m_enemy.itemDrop = true;
				SOUNDMANAGER->play("�ź���_����");
			}
			//���� ü���� �������� ��� �ǰ� ��� �ߵ�
			else
			{
				m_enemy.current = HIT_ENEMY;
				SOUNDMANAGER->play("�ź���_�ǰ�");
			}
		}
	}

	//���ʹ� ���� ü�� ����
	virtual void setHP1(int hp) { m_enemy.currentHP = hp; }

	//���ʹ� Ž���߳�?
	bool getIsDetection() { return m_enemy.isDetection; }
	void setIsDetection(bool isDetection) { m_enemy.isDetection = isDetection; }

	//���ʹ� ������ ���� �ֳ�?
	void setIsLeft(bool isLeft) { m_enemy.isLeft = isLeft; }


	//���ʹ� ���� ����
	void setCurrent(currentEnemy current)
	{
		m_enemy.current = current;
		m_enemy.count = m_enemy.currentFrameX = 0;
	}

	bool getItemDrop() { return m_enemy.itemDrop; }
	void setItemDrop(bool itemDrop) { m_enemy.itemDrop = itemDrop; }

	//�߰� �Լ�->��ܿ� �����߰�
	bool getFire() { return m_enemy.fire; }
	void setFire(bool _fire) { m_enemy.fire = _fire; }
	float getFireDelay() { return m_enemy.fireDelay; }
	void setFireDelay(float _delay) { m_enemy.fireDelay = _delay; }

	int getEnemyNumber() { return m_enemy.enemyNumber; }
	void setEnemyNumber(int _number) { m_enemy.enemyNumber = _number; }

	bool getFireEnemy() { return m_enemy.fireEnemy; }
	bool fireCheck();
};

//���� Ŭ����
class duck : public enemy
{
private:
	tagEnemy m_enemy;
	progressBar* m_progressBar;
public:
	duck();
	~duck();

	HRESULT init(POINT position);
	void release();
	void update();
	void render(POINT pt);

	void detection();
	void animation();
	void dashCoolTime();
	bool dash();
	bool dead();
	void walkCoolTime();
	void walk();

	//���ʹ� ��ü ��Ʈ
	RECT getRect() { return m_enemy.rc; }

	//���ʹ� Ž���Ÿ� ��Ʈ
	RECT getDetectionRect() { return m_enemy.detectionRc; }

	RECT getCollisionRect() { return m_enemy.collisionRc; }
	//���ʹ� X
	float getX() { return m_enemy.x; }
	void setX(float x) { m_enemy.x = x; }

	//���ʹ� Y
	float getY() { return m_enemy.y; }
	void setY(float y) { m_enemy.y = y; }

	//���ʹ� �ޱ�
	float getAngle() { return m_enemy.angle; }
	void setAngle(float angle) { m_enemy.angle = angle; }

	//���ʹ� ���� ü�� ����
	void setHP(int hp)
	{
		if (m_enemy.current != DEAD_ENEMY)
		{
			m_enemy.currentHP -= hp;
			m_enemy.count = 0;
			m_enemy.currentFrameX = 0;
			//���� ü���� ���� ��� ���� ��� �ߵ�
			if (m_enemy.currentHP <= 0)
			{
				m_enemy.current = DEAD_ENEMY;
				m_enemy.itemDrop = true;
				SOUNDMANAGER->play("����_����");
			}
			//���� ü���� �������� ��� �ǰ� ��� �ߵ�
			else m_enemy.current = HIT_ENEMY;
		}
	}

	bool getItemDrop() { return m_enemy.itemDrop; }
	void setItemDrop(bool itemDrop) { m_enemy.itemDrop = itemDrop; }

	//���ʹ� ���� ü�� ����
	virtual void setHP1(int hp) { m_enemy.currentHP = hp; }

	//���ʹ� Ž���߳�?
	bool getIsDetection() { return m_enemy.isDetection; }
	void setIsDetection(bool isDetection) { m_enemy.isDetection = isDetection; }

	//���ʹ� ������ ���� �ֳ�?
	void setIsLeft(bool isLeft) { m_enemy.isLeft = isLeft; }

	//���ʹ� ���� ����
	currentEnemy getCurrent() { return m_enemy.current; }
	void setCurrent(currentEnemy current)
	{
		m_enemy.current = current;
		m_enemy.count = m_enemy.currentFrameX = 0;
	}

	//�߰� �Լ�->��ܿ� �����߰�
	bool getFire() { return m_enemy.fire; }
	void setFire(bool _fire) { m_enemy.fire = _fire; }
	float getFireDelay() { return m_enemy.fireDelay; }
	void setFireDelay(float _delay) { m_enemy.fireDelay = _delay; }

	int getEnemyNumber() { return m_enemy.enemyNumber; }
	void setEnemyNumber(int _number) { m_enemy.enemyNumber = _number; }

	bool getFireEnemy() { return m_enemy.fireEnemy; }
};

//���̰��� Ŭ����
class kamikaze : public enemy
{
private:
	tagEnemy m_enemy;
	progressBar* m_progressBar;
public:
	kamikaze();
	~kamikaze();

	HRESULT init(POINT position);
	void release();
	void update();
	void render(POINT pt);

	void detection();
	void animation();
	void dashCoolTime();
	bool dash();
	bool dead();
	void walkCoolTime();
	void walk();

	//���ʹ� ��ü ��Ʈ
	RECT getRect() { return m_enemy.rc; }

	//���ʹ� Ž���Ÿ� ��Ʈ
	RECT getDetectionRect() { return m_enemy.detectionRc; }

	RECT getCollisionRect() { return m_enemy.collisionRc; }
	//���ʹ� X
	float getX() { return m_enemy.x; }
	void setX(float x) { m_enemy.x = x; }

	//���ʹ� Y
	float getY() { return m_enemy.y; }
	void setY(float y) { m_enemy.y = y; }


	//���ʹ� �ޱ�
	float getAngle() { return m_enemy.angle; }
	void setAngle(float angle) { m_enemy.angle = angle; }

	//���ʹ� ���� ü�� ����
	void setHP(int hp)
	{
		if (m_enemy.current != DEAD_ENEMY)
		{
			m_enemy.currentHP -= hp;
			m_enemy.count = 0;
			m_enemy.currentFrameX = 0;
			
			//���� ü���� ���� ��� ���� ��� �ߵ�
			if (m_enemy.currentHP <= 0)
			{
				m_enemy.current = DEAD_ENEMY;
				m_enemy.itemDrop = true;
				SOUNDMANAGER->play("���̰���_����");
			}
			//���� ü���� �������� ��� �ǰ� ��� �ߵ�
			else
			{
				m_enemy.current = HIT_ENEMY;
				SOUNDMANAGER->play("���̰���_�ǰ�");
			}
		}
	}


	bool getItemDrop() { return m_enemy.itemDrop; }
	void setItemDrop(bool itemDrop) { m_enemy.itemDrop = itemDrop; }

	//���ʹ� ���� ü�� ����
	void setHP1(int hp) { m_enemy.currentHP = hp; }

	//���ʹ� Ž���߳�?
	bool getIsDetection() { return m_enemy.isDetection; }
	void setIsDetection(bool isDetection) { m_enemy.isDetection = isDetection; }

	//���ʹ� ������ ���� �ֳ�?
	void setIsLeft(bool isLeft) { m_enemy.isLeft = isLeft; }

	//���ʹ� ���� ����
	currentEnemy getCurrent() { return m_enemy.current; }
	void setCurrent(currentEnemy current)
	{
		m_enemy.current = current;
		m_enemy.count = m_enemy.currentFrameX = 0;
	}

	//�߰� �Լ�->��ܿ� �����߰�
	bool getFire() { return m_enemy.fire; }
	void setFire(bool _fire) { m_enemy.fire = _fire; }
	float getFireDelay() { return m_enemy.fireDelay; }
	void setFireDelay(float _delay) { m_enemy.fireDelay = _delay; }

	int getEnemyNumber() { return m_enemy.enemyNumber; }
	void setEnemyNumber(int _number) { m_enemy.enemyNumber = _number; }

	bool getFireEnemy() { return m_enemy.fireEnemy; }
};