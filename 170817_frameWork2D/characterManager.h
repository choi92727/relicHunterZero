#pragma once
#include "gameNode.h"
#include "characterInterface.h"
#include "jimmy.h"
#include "rider.h"
#include "characterClassic.h"
class characterManager : public gameNode
{
private:
	characterInterface* m_player;
	selectCharacter character;
public:
	characterManager();
	~characterManager();

	HRESULT init(POINT position, selectCharacter chara);
	void release();
	void update();
	void render();

	float getPlayerX() { return m_player->getPlayerX(); }			//플레이어 X Y 겟셋
	void setPlayerX(float setX) { m_player->setPlayerX(setX); }
	float getPlayerY() { return m_player->getPlayerY(); }
	void setPlayerY(float setY) { m_player->setPlayerY(setY); }

	RECT getEnemy_hitRc() { return m_player->getEnemy_hitRc(); }//플레이어 피격히트박스 가져오기
	RECT getWall_hitRc() { return m_player->getWall_hitRc(); }	//플레이어 벽히트박스 가져오기

	int getMaxHP() { return m_player->getMaxHP(); }		//플레이어 총체력가져오기
	void setMaxHP(int HP) { m_player->setMaxHP(HP); }	//총체력 셋
	int getCurrentHP() { return m_player->getCurrentHP(); }		//플레이어 현재체력가져오기
	void setCurrentHP(int HP) { m_player->setCurrentHP(HP); }	//현제체력 셋

	int getMaxShield() { return m_player->getMaxShield(); }		//플레이어 쉴드가져오기
	void setMaxShield(int shield) { m_player->setMaxShield(shield); }	//플레이어 쉴드셋
	int getCurrentShield() { return m_player->getCurrentShield(); }		//플레이어 쉴드가져오기
	void setCurrentShield(int shield) { m_player->setCurrentShield(shield); }	//플레이어 쉴드셋
	
};

