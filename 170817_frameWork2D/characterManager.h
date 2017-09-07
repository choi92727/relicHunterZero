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

	float getPlayerX() { return m_player->getPlayerX(); }			//�÷��̾� X Y �ټ�
	void setPlayerX(float setX) { m_player->setPlayerX(setX); }
	float getPlayerY() { return m_player->getPlayerY(); }
	void setPlayerY(float setY) { m_player->setPlayerY(setY); }

	RECT getEnemy_hitRc() { return m_player->getEnemy_hitRc(); }//�÷��̾� �ǰ���Ʈ�ڽ� ��������
	RECT getWall_hitRc() { return m_player->getWall_hitRc(); }	//�÷��̾� ����Ʈ�ڽ� ��������

	int getMaxHP() { return m_player->getMaxHP(); }		//�÷��̾� ��ü�°�������
	void setMaxHP(int HP) { m_player->setMaxHP(HP); }	//��ü�� ��
	int getCurrentHP() { return m_player->getCurrentHP(); }		//�÷��̾� ����ü�°�������
	void setCurrentHP(int HP) { m_player->setCurrentHP(HP); }	//����ü�� ��

	int getMaxShield() { return m_player->getMaxShield(); }		//�÷��̾� ���尡������
	void setMaxShield(int shield) { m_player->setMaxShield(shield); }	//�÷��̾� �����
	int getCurrentShield() { return m_player->getCurrentShield(); }		//�÷��̾� ���尡������
	void setCurrentShield(int shield) { m_player->setCurrentShield(shield); }	//�÷��̾� �����
	
};

