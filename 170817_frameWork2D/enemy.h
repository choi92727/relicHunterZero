#pragma once
#include "gameNode.h"
#include "progressBar.h"

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
	float dashAngle;						//����, ���̰��� ����
	int dashCoolTime, dashCoolTimeMax;		//����, ���̰��� ����
	float dash, acceleration;				//����, ���̰��� ����
	int count, detectionCount;
	int currentFrameX, currentFrameY;
	int detectionX;
	bool isDetection, detection;
	bool isLeft;
	currentEnemy current;
	RECT collisionRc;
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

	//���ʹ� ���� ü�� ����
	virtual void setHP(int hp)
	{
		if (m_enemy.current != DEAD_ENEMY)
		{
			m_enemy.currentHP -= hp;
			m_enemy.count = 0;
			m_enemy.currentFrameX = 0;
			//���� ü���� ���� ��� ���� ��� �ߵ�
			if (m_enemy.currentHP <= 0) m_enemy.current = DEAD_ENEMY;
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
			if (m_enemy.currentHP <= 0) m_enemy.current = DEAD_ENEMY;
			//���� ü���� �������� ��� �ǰ� ��� �ߵ�
			else m_enemy.current = HIT_ENEMY;
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
	currentEnemy getCurrent() { return m_enemy.current; }
	void setCurrent(currentEnemy current)
	{
		m_enemy.current = current;
		m_enemy.count = m_enemy.currentFrameX = 0;
	}
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
			if (m_enemy.currentHP <= 0) m_enemy.current = DEAD_ENEMY;
			//���� ü���� �������� ��� �ǰ� ��� �ߵ�
			else m_enemy.current = HIT_ENEMY;
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
	currentEnemy getCurrent() { return m_enemy.current; }
	void setCurrent(currentEnemy current)
	{
		m_enemy.current = current;
		m_enemy.count = m_enemy.currentFrameX = 0;
	}
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
			if (m_enemy.currentHP <= 0) m_enemy.current = DEAD_ENEMY;
			//���� ü���� �������� ��� �ǰ� ��� �ߵ�
			else m_enemy.current = HIT_ENEMY;
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
	currentEnemy getCurrent() { return m_enemy.current; }
	void setCurrent(currentEnemy current)
	{
		m_enemy.current = current;
		m_enemy.count = m_enemy.currentFrameX = 0;
	}
};