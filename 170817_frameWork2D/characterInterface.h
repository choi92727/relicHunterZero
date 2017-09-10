#pragma once
#include "gameNode.h"
#include "characterProgressBar.h"
#include "numberDrawManager.h"

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
		image* faceImg;		//���̹���

		image* shieldImg;	//�����̹���
		bool shieldRender;	//����׷��ֱ�

		RECT enemy_hitRc;	//������ �´� ��Ʈ�ڽ�
		RECT wall_hitRc;	//���� �浹�ϴ� �ڽ�

		RECT melee_atkRc;	//���������ϴ� ��Ʈ

		float x, y;
		int currentHP, maxHP;			//ü��
		int currentShield, maxShield;	//����

		float shieldGenDealy;	//������Ÿ�ӵ�����;
		float shieldGenTime;	//������Ÿ��
		bool shieldGen;		//������

		int currentStamina, maxStamina;	//���׹̳�
		float speed;
		float angle;
		currentAnimation animation;
		float gunDelay;			//�� ������

		int frameCount;
		int frameX, frameY;

		bool life;
		bool isLeft;


		bool meleeAtk;//�������� ��Ʈ����
		bool meleeAtkOnce;//�ѹ�������
		bool meleeEnd = false;//���������� ����


		bool run;	//�޸��������� Ȯ��
		bool runStartDelay;	//���׹̳� 10�̻��϶����޸���

		bool dash;		//�뽬 ������ Ȯ��
		bool melee;		//�������� ������ Ȯ��
		bool hit;		//���� �޾Ҵ��� Ȯ��
		bool damage;	//������������ ����������

		bool die; //������������ �Ұ�

		bool teleporting = false; //�ڷ���Ʈ���ΰ�?
		tagCharacter nowCharacter;

		bool completeTeleport = false;
	};

	tagPlayer m_player;

	characterProgressBar* hpBar;
	characterProgressBar* shieldBar;
	characterProgressBar* staminaBar;

	numberDrawManager* hpNumDraw;
	numberDrawManager* shieldNumDraw;




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

	bool dashOnce;
	bool once = true;	//�ѹ�������ǰ� �ϴ� bool ����
	bool dash;
public:
	characterInterface();
	virtual ~characterInterface();

	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update(POINT pt);
	virtual void render(POINT pt);

	virtual void animation();
	virtual void move();
	virtual void command();
	virtual void melee(POINT pt);
	virtual void hit();
	virtual void dead();
	virtual void fire();

	virtual void run();
	virtual void hpFaceInfo();

	virtual void shieldRegen();

	virtual void damage();

	float getPlayerX() { return m_player.x; }			//�÷��̾� X Y �ټ�
	void setPlayerX(float setX) { m_player.x = setX; }
	float getPlayerY() { return m_player.y; }
	void setPlayerY(float setY) { m_player.y = setY; }

	RECT getEnemy_hitRc() { return m_player.enemy_hitRc; }//�÷��̾� �ǰ���Ʈ�ڽ� ��������
	RECT getWall_hitRc() { return m_player.wall_hitRc; }	//�÷��̾� ����Ʈ�ڽ� ��������

	bool getMeleeAtk() { return m_player.meleeAtk; }
	RECT getMelee_atkRc() { return m_player.melee_atkRc; }//�÷��̾� �������� ��Ʈ ��������@@@@@@@@@
	float getP_Angle() { return m_player.angle; }
	float getSpeed() { return m_player.speed; }
	bool getMeleeEnd() { return m_player.meleeEnd; }

	int getMaxHP() { return m_player.maxHP; }		//�÷��̾� ��ü�°�������
	void setMaxHP(int HP) { m_player.maxHP = HP; }	//��ü�� ��
	int getCurrentHP() { return m_player.currentHP; }		//�÷��̾� ����ü�°�������
	void setCurrentHP(int HP) { m_player.currentHP = HP; }	//����ü�� ��

	int getMaxShield() { return m_player.maxShield; }		//�÷��̾� ���尡������
	void setMaxShield(int shield) { m_player.maxShield = shield; }	//�÷��̾� �����
	int getCurrentShield() { return m_player.currentShield; }		//�÷��̾� ���尡������
	void setCurrentShield(int shield) { m_player.currentShield = shield; }	//�÷��̾� �����

																			//	bool getMeleeAtk() { return m_player.meleeAtk; }
	void setMeleeAtk(bool MeleeAtk) { m_player.meleeAtk = MeleeAtk; }

	bool getIsleft() { return m_player.isLeft; }
	void setIsleft(bool isleft) { m_player.isLeft = isleft; }

	virtual void damageBullet(float damage);

	virtual void isTeleport();

	bool getCompleteTeleport() { return m_player.completeTeleport; }
};

