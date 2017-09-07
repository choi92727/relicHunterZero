#pragma once
#include "gameNode.h"

class characterInterface : public gameNode
{

protected:
	//에너미 현재 애니메이션 상태
	enum currentAnimation
	{
		DASH,	//대쉬 >>
		DEATH,	//죽음
		DIG,	//땅파기
		HIT,	//피격
		IDLE,	//기본(정지)
		MELEE,	//근접공격
		RUN,	//달리기
		TELEPORT,	//텔레포트
		WALK		//기본이동
	};

	//현재 캐릭터 ENUM문
	enum tagCharacter
	{
		JIMMY, RIDER
	};

	//플레이어 구조체
	struct tagPlayer
	{
		image* img;			//이미지
		RECT enemy_hitRc;	//적에게 맞는 히트박스
		RECT wall_hitRc;
		float x, y;
		int currentHP, maxHP;			//체력
		int currentShield, maxShield;	//쉴드
		int staminaAll, staminaDash;	//총스테미너 , 대쉬가 가능한 스테미너
		float speed;
		float angle;
		currentAnimation animation;
		float gunDelay;			//총 딜레이

		int frameCount;
		int frameX, frameY;

		
		bool life;
		bool isLeft;
		bool dash;		//대쉬 중인지 확인
		bool melee;		//근접공격 중인지 확인
		bool hit;		//대미지를 받았는지 확인
		tagCharacter nowCharacter;
	};

	tagPlayer m_player;



	enum eKey	//커맨드 값을 입력받기위한 enum문
	{
		key_left,
		key_up,
		key_right,
		key_down
	};

	TCHAR _str[128];

	vector<BYTE > _vCOMMAND;
	
	float _fCommandTime;
	float _fCommandClear;


	bool once = true;	//한번만실행되게 하는 bool 변수

public:
	characterInterface();
	virtual ~characterInterface();

	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render(POINT pt);

	virtual void animation();
	virtual void move();
	virtual void command();
	virtual void melee();
	virtual void hit();
	virtual void dead();
	virtual void fire();


	float getPlayerX() { return m_player.x; }			//플레이어 X Y 겟셋
	void setPlayerX(float setX) { m_player.x = setX; }
	float getPlayerY() { return m_player.y; }
	void setPlayerY(float setY) { m_player.y = setY; }

	RECT getEnemy_hitRc() { return m_player.enemy_hitRc; }//플레이어 피격히트박스 가져오기
	RECT getWall_hitRc() { return m_player.wall_hitRc; }	//플레이어 벽히트박스 가져오기

	int getMaxHP() { return m_player.maxHP; }		//플레이어 총체력가져오기
	void setMaxHP(int HP) { m_player.maxHP = HP; }	//총체력 셋
	int getCurrentHP() { return m_player.currentHP; }		//플레이어 현재체력가져오기
	void setCurrentHP(int HP) { m_player.currentHP = HP; }	//현제체력 셋

	int getMaxShield() { return m_player.maxShield; }		//플레이어 쉴드가져오기
	void setMaxShield(int shield) { m_player.maxShield = shield; }	//플레이어 쉴드셋
	int getCurrentShield() { return m_player.currentShield; }		//플레이어 쉴드가져오기
	void setCurrentShield(int shield) { m_player.currentShield = shield; }	//플레이어 쉴드셋
};

