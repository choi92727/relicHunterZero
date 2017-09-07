#pragma once
#include "gameNode.h"

class characterInterface : public gameNode
{

protected:
	//���ʹ� ���� �ִϸ��̼� ����
	enum currentAnimation
	{
		DASH,	//�뽬 >>
		DEATH,	//����
		DIG,	//���ı�
		HIT,	//�ǰ�
		IDLE,	//�⺻(����)
		MELEE,	//��������
		RUN,	//�޸���
		TELEPORT,	//�ڷ���Ʈ
		WALK		//�⺻�̵�
	};

	//���� ĳ���� ENUM��
	enum tagCharacter
	{
		JIMMY, RIDER
	};

	//�÷��̾� ����ü
	struct tagPlayer
	{
		image* img;			//�̹���
		RECT enemy_hitRc;	//������ �´� ��Ʈ�ڽ�
		RECT wall_hitRc;
		float x, y;
		int currentHP, maxHP;			//ü��
		int currentShield, maxShield;	//����
		int staminaAll, staminaDash;	//�ѽ��׹̳� , �뽬�� ������ ���׹̳�
		float speed;
		float angle;
		currentAnimation animation;
		float gunDelay;			//�� ������

		int frameCount;
		int frameX, frameY;

		
		bool life;
		bool isLeft;
		bool dash;		//�뽬 ������ Ȯ��
		bool melee;		//�������� ������ Ȯ��
		bool hit;		//������� �޾Ҵ��� Ȯ��
		tagCharacter nowCharacter;
	};

	tagPlayer m_player;



	enum eKey	//Ŀ�ǵ� ���� �Է¹ޱ����� enum��
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


	bool once = true;	//�ѹ�������ǰ� �ϴ� bool ����

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


	float getPlayerX() { return m_player.x; }			//�÷��̾� X Y �ټ�
	void setPlayerX(float setX) { m_player.x = setX; }
	float getPlayerY() { return m_player.y; }
	void setPlayerY(float setY) { m_player.y = setY; }

	RECT getEnemy_hitRc() { return m_player.enemy_hitRc; }//�÷��̾� �ǰ���Ʈ�ڽ� ��������
	RECT getWall_hitRc() { return m_player.wall_hitRc; }	//�÷��̾� ����Ʈ�ڽ� ��������

	int getMaxHP() { return m_player.maxHP; }		//�÷��̾� ��ü�°�������
	void setMaxHP(int HP) { m_player.maxHP = HP; }	//��ü�� ��
	int getCurrentHP() { return m_player.currentHP; }		//�÷��̾� ����ü�°�������
	void setCurrentHP(int HP) { m_player.currentHP = HP; }	//����ü�� ��

	int getMaxShield() { return m_player.maxShield; }		//�÷��̾� ���尡������
	void setMaxShield(int shield) { m_player.maxShield = shield; }	//�÷��̾� �����
	int getCurrentShield() { return m_player.currentShield; }		//�÷��̾� ���尡������
	void setCurrentShield(int shield) { m_player.currentShield = shield; }	//�÷��̾� �����
};

