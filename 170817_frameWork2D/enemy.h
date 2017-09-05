#pragma once
#include "gameNode.h"
#include "progressBar.h"

//에너미 현재 상태
enum currentEnemy
{
	STOP_ENEMY,		//(정지) 공통
	MOVE_ENEMY,		//(이동) 공통
	HIT_ENEMY,		//(피격) 공통
	DEAD_ENEMY,		//(죽음) 공통
	DASH_ENEMY,		//(대쉬) 오리, 가미가제 전용
};

//에너미 구조체
struct tagEnemy
{
	image* image;
	RECT rc;
	RECT detection;
	float x, y;
	int currentHP, maxHP;
	float speed;
	float angle;
	int dashCoolTime, dashCoolTimeMax;		//오리, 가미가제 전용
	float dash, acceleration;				//오리, 가미가제 전용
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

//거북이 클래스
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

//오리 클래스
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

//가미가제 클래스
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