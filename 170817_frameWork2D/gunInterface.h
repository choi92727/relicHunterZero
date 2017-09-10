#pragma once
#include "gameNode.h"
#include "bulletInterface.h"
#include "bulletManager.h"
#include "numberDrawManager.h"
class gunInterface : public gameNode
{
protected:
	float m_damage;//총기 데미지
	float m_speed;//총기속도
	float m_angle;//각도
	float m_x;//가로좌표
	float m_y;//세로좌표
	float m_fireDelay;//총알을 쏘는 제한시간
	float m_isDelay;//실제 도는 제한시간
	bool m_fire;//발사 가능한지 여부
	
	Image* m_gunImage[2];//이미지 회전 시 필요한 변수
	Graphics* m_graphics;//이미지 회전시 필요한 변수
	CHARACTER m_playerType;//플레이어 타입 변수
	bulletManager* m_bulletManager;//불렛매니저 연동
	GUNTYPE m_gunType;
	numberDrawManager m_currentDraw;
	numberDrawManager m_totalDraw;

	int m_currentBullet;
	int m_maxBullet;
	int m_totalBullet;

	//에너미용 변수
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
	void setAngle(float angle) { m_angle = angle; }//앵글을 새로 넣어준다
	virtual void setPosition(int x, int y);//포지션 재설정
	float getFireDelay() { return m_fireDelay; }
	void reload();
	GUNTYPE getGunType() { return m_gunType; }
	void setBulletManagerLink(bulletManager &_bulletManager) { m_bulletManager = &_bulletManager; }
	//총알 발사시마다 불렛 매니저에서 넣어줌

	//에너미 사용함수
	int getGunIndex() { return m_gunIndex; }
	void setGunIndex(int _gunIndex) { m_gunIndex = _gunIndex; }

	bool getEnemyFireTriger() { return m_enemy_fire; }
	void setEnemyFireTriger(bool _bool){ m_enemy_fire = _bool; }

	bool getCanFire() { return m_canFire; }
	void setCanFire(bool _setFire) {m_canFire = _setFire; }



};

