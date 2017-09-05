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
	RECT detection;
	float x, y;
	int currentHP, maxHP;
	float speed;
	float angle;
	int dashCoolTime, dashCoolTimeMax;		//����, ���̰��� ����
	float dash, acceleration;				//����, ���̰��� ����
	int count;
	int currentFrameX, currentFrameY;
	bool isDetection;
	bool isLeft;
	currentEnemy current;
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
	virtual void render();

	virtual void animation();
	virtual bool dead();

	virtual RECT getRect() { return m_enemy.rc; }
	virtual RECT getDetectionRect() { return m_enemy.detection; }
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
	void render();

	void animation();
	bool dead();
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
	void render();

	void animation();
	void dashCoolTime();
	bool dash();
	bool dead();
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
	void render();

	void animation();
	void dashCoolTime();
	bool dash();
	bool dead();
};