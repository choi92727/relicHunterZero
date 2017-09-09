#pragma once
#include "gameNode.h"
#include "progressBar.h"

class gunInterface;


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
	RECT detectionRc;
	RECT collisionRc;
	float x, y;
	int currentHP, maxHP;
	float speed;
	float angle;
	float dashAngle;						//오리, 가미가제 전용
	int dashCoolTime, dashCoolTimeMax;		//오리, 가미가제 전용
	float dash, acceleration;				//오리, 가미가제 전용
	int count, detectionCount;
	int currentFrameX, currentFrameY;
	int detectionX;
	bool isDetection, detection;
	bool isLeft;
	currentEnemy current;
	//총알 발사 변수
	bool fire = true;
	float fireDelay= 1.5f * 60.0f;//총알 발사 대기시간
	bool fireEnemy = false;//총을 쏘는 에너미인지
	int enemyNumber = 0;//현재 에너미의 숫자값
	
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

	//에너미 몸체 렉트
	virtual RECT getRect() { return m_enemy.rc; }

	//에너미 탐지거리 렉트
	virtual RECT getDetectionRect() { return m_enemy.detectionRc; }
	virtual RECT getCollisionRect() { return m_enemy.collisionRc; }
	

	//에너미 X
	virtual float getX() { return m_enemy.x; }
	virtual void setX(float x) { m_enemy.x = x; }

	//에너미 Y
	virtual float getY() { return m_enemy.y; }
	virtual void setY(float y) { m_enemy.y = y; }

	//에너미 앵글
	virtual float getAngle() { return m_enemy.angle; }
	virtual void setAngle(float angle) { m_enemy.angle = angle; }

	//문광현 추가한 함수
	 bool getFire() { return m_enemy.fire; }
	 void setFire(bool _fire) { m_enemy.fire = _fire; }
	 float getFireDelay() { return m_enemy.fireDelay; }
	 void setFireDelay(float _delay) { m_enemy.fireDelay = _delay; }
	
	 int getEnemyNumber() { return m_enemy.enemyNumber; }
	 void setEnemyNumber(int _number) { m_enemy.enemyNumber = _number; }

	 bool getFireEnemy() { return m_enemy.fireEnemy; }
	 virtual bool fireCheck();

	//에너미 현재 체력 수정
	virtual void setHP(int hp)
	{
		if (m_enemy.current != DEAD_ENEMY)
		{
			m_enemy.currentHP -= hp;
			m_enemy.count = 0;
			m_enemy.currentFrameX = 0;
			//현재 체력이 없을 경우 죽음 모션 발동
			if (m_enemy.currentHP <= 0) m_enemy.current = DEAD_ENEMY;
			//현재 체력이 남아있을 경우 피격 모션 발동
			else m_enemy.current = HIT_ENEMY;
		}
	}

	//에너미 현재 체력 수정
	virtual void setHP1(int hp) { m_enemy.currentHP = hp; }

	//에너미 탐지했냐?
	virtual bool getIsDetection() { return m_enemy.isDetection; }
	virtual void setIsDetection(bool isDetection) { m_enemy.isDetection = isDetection; }

	//에너미 왼쪽을 보고 있냐?
	virtual void setIsLeft(bool isLeft) { m_enemy.isLeft = isLeft; }

	//에너미 현재 상태
	virtual currentEnemy getCurrent() { return m_enemy.current; }
	virtual void setCurrent(currentEnemy current)
	{
		m_enemy.current = current;
		m_enemy.count = m_enemy.currentFrameX = 0;
	}
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
	void render(POINT pt);

	void detection();
	void animation();
	bool dead();

	//에너미 몸체 렉트
	RECT getRect() { return m_enemy.rc; }

	//에너미 탐지거리 렉트
	RECT getDetectionRect() { return m_enemy.detectionRc; }

	RECT getCollisionRect() { return m_enemy.collisionRc; }
	//에너미 X
	float getX() { return m_enemy.x; }
	void setX(float x) { m_enemy.x = x; }

	//에너미 Y
	float getY() { return m_enemy.y; }
	void setY(float y) { m_enemy.y = y; }

	//에너미 앵글
	float getAngle() { return m_enemy.angle; }
	void setAngle(float angle) { m_enemy.angle = angle; }

	//에너미 현재 체력 수정
	void setHP(int hp)
	{
		if (m_enemy.current != DEAD_ENEMY)
		{
			m_enemy.currentHP -= hp;
			m_enemy.count = 0;
			m_enemy.currentFrameX = 0;
			//현재 체력이 없을 경우 죽음 모션 발동
			if (m_enemy.currentHP <= 0) m_enemy.current = DEAD_ENEMY;
			//현재 체력이 남아있을 경우 피격 모션 발동
			else m_enemy.current = HIT_ENEMY;
		}
	}

	//에너미 현재 체력 수정
	virtual void setHP1(int hp) { m_enemy.currentHP = hp; }

	//에너미 탐지했냐?
	bool getIsDetection() { return m_enemy.isDetection; }
	void setIsDetection(bool isDetection) { m_enemy.isDetection = isDetection; }

	//에너미 왼쪽을 보고 있냐?
	void setIsLeft(bool isLeft) { m_enemy.isLeft = isLeft; }

	//에너미 현재 상태
	currentEnemy getCurrent() { return m_enemy.current; }
	void setCurrent(currentEnemy current)
	{
		m_enemy.current = current;
		m_enemy.count = m_enemy.currentFrameX = 0;
	}

	//추가 함수->상단에 설명추가
	bool getFire() { return m_enemy.fire; }
	void setFire(bool _fire) { m_enemy.fire = _fire; }
	float getFireDelay() { return m_enemy.fireDelay; }
	void setFireDelay(float _delay) { m_enemy.fireDelay = _delay; }

	int getEnemyNumber() { return m_enemy.enemyNumber; }
	void setEnemyNumber(int _number) { m_enemy.enemyNumber = _number; }

	bool getFireEnemy() { return m_enemy.fireEnemy; }
	bool fireCheck();
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
	void render(POINT pt);

	void detection();
	void animation();
	void dashCoolTime();
	bool dash();
	bool dead();

	//에너미 몸체 렉트
	RECT getRect() { return m_enemy.rc; }

	//에너미 탐지거리 렉트
	RECT getDetectionRect() { return m_enemy.detectionRc; }

	RECT getCollisionRect() { return m_enemy.collisionRc; }
	//에너미 X
	float getX() { return m_enemy.x; }
	void setX(float x) { m_enemy.x = x; }

	//에너미 Y
	float getY() { return m_enemy.y; }
	void setY(float y) { m_enemy.y = y; }

	//에너미 앵글
	float getAngle() { return m_enemy.angle; }
	void setAngle(float angle) { m_enemy.angle = angle; }

	//에너미 현재 체력 수정
	void setHP(int hp)
	{
		if (m_enemy.current != DEAD_ENEMY)
		{
			m_enemy.currentHP -= hp;
			m_enemy.count = 0;
			m_enemy.currentFrameX = 0;
			//현재 체력이 없을 경우 죽음 모션 발동
			if (m_enemy.currentHP <= 0) m_enemy.current = DEAD_ENEMY;
			//현재 체력이 남아있을 경우 피격 모션 발동
			else m_enemy.current = HIT_ENEMY;
		}
	}

	//에너미 현재 체력 수정
	virtual void setHP1(int hp) { m_enemy.currentHP = hp; }

	//에너미 탐지했냐?
	bool getIsDetection() { return m_enemy.isDetection; }
	void setIsDetection(bool isDetection) { m_enemy.isDetection = isDetection; }

	//에너미 왼쪽을 보고 있냐?
	void setIsLeft(bool isLeft) { m_enemy.isLeft = isLeft; }

	//에너미 현재 상태
	currentEnemy getCurrent() { return m_enemy.current; }
	void setCurrent(currentEnemy current)
	{
		m_enemy.current = current;
		m_enemy.count = m_enemy.currentFrameX = 0;
	}

	//추가 함수->상단에 설명추가
	bool getFire() { return m_enemy.fire; }
	void setFire(bool _fire) { m_enemy.fire = _fire; }
	float getFireDelay() { return m_enemy.fireDelay; }
	void setFireDelay(float _delay) { m_enemy.fireDelay = _delay; }

	int getEnemyNumber() { return m_enemy.enemyNumber; }
	void setEnemyNumber(int _number) { m_enemy.enemyNumber = _number; }

	bool getFireEnemy() { return m_enemy.fireEnemy; }
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
	void render(POINT pt);

	void detection();
	void animation();
	void dashCoolTime();
	bool dash();
	bool dead();

	//에너미 몸체 렉트
	RECT getRect() { return m_enemy.rc; }

	//에너미 탐지거리 렉트
	RECT getDetectionRect() { return m_enemy.detectionRc; }

	RECT getCollisionRect() { return m_enemy.collisionRc; }
	//에너미 X
	float getX() { return m_enemy.x; }
	void setX(float x) { m_enemy.x = x; }

	//에너미 Y
	float getY() { return m_enemy.y; }
	void setY(float y) { m_enemy.y = y; }


	//에너미 앵글
	float getAngle() { return m_enemy.angle; }
	void setAngle(float angle) { m_enemy.angle = angle; }

	//에너미 현재 체력 수정
	void setHP(int hp)
	{
		if (m_enemy.current != DEAD_ENEMY)
		{
			m_enemy.currentHP -= hp;
			m_enemy.count = 0;
			m_enemy.currentFrameX = 0;
			//현재 체력이 없을 경우 죽음 모션 발동
			if (m_enemy.currentHP <= 0) m_enemy.current = DEAD_ENEMY;
			//현재 체력이 남아있을 경우 피격 모션 발동
			else m_enemy.current = HIT_ENEMY;
		}
	}

	//에너미 현재 체력 수정
	virtual void setHP1(int hp) { m_enemy.currentHP = hp; }

	//에너미 탐지했냐?
	bool getIsDetection() { return m_enemy.isDetection; }
	void setIsDetection(bool isDetection) { m_enemy.isDetection = isDetection; }

	//에너미 왼쪽을 보고 있냐?
	void setIsLeft(bool isLeft) { m_enemy.isLeft = isLeft; }

	//에너미 현재 상태
	currentEnemy getCurrent() { return m_enemy.current; }
	void setCurrent(currentEnemy current)
	{
		m_enemy.current = current;
		m_enemy.count = m_enemy.currentFrameX = 0;
	}

	//추가 함수->상단에 설명추가
	bool getFire() { return m_enemy.fire; }
	void setFire(bool _fire) { m_enemy.fire = _fire; }
	float getFireDelay() { return m_enemy.fireDelay; }
	void setFireDelay(float _delay) { m_enemy.fireDelay = _delay; }

	int getEnemyNumber() { return m_enemy.enemyNumber; }
	void setEnemyNumber(int _number) { m_enemy.enemyNumber = _number; }

	bool getFireEnemy() { return m_enemy.fireEnemy; }
};