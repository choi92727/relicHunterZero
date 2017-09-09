#include "stdafx.h"
#include "rider.h"


rider::rider()
{
}


rider::~rider()
{
}

HRESULT rider::init(POINT position)
{

	_fCommandClear = 2.5f;	//Ŀ�ǵ��Է½ð�
	_fCommandTime = 0.0f;
	
	ZeroMemory(&m_player, sizeof(m_player));

	m_player.img = IMAGEMANAGER->findImage("���̴�");		//���̴� �̹���������
	m_player.faceImg = IMAGEMANAGER->findImage("���̴����¾�");		//ü�¿����� ���̴���
	m_player.x = position.x;
	m_player.y = position.y;
	m_player.enemy_hitRc = RectMakeCenter(m_player.x, m_player.y, 34, 72);	//������ �ǰݰ����� ��Ʈ
	m_player.wall_hitRc = RectMakeCenter(m_player.x, m_player.y + 32, 56, 22);	//���� �ε�ġ�� ��Ʈ
	m_player.currentHP = m_player.maxHP = 100;
	m_player.currentShield = m_player.maxShield = 50;
	m_player.currentStamina = m_player.maxStamina = 100;	//
	m_player.speed = 5.0f;													//�÷��̾� �̵��ӵ�
	m_player.frameCount = 0;
	m_player.frameX = 0;
	m_player.frameY = 0;
	m_player.isLeft = false;												//�÷��̾� ���ʺ��°�?
	m_player.animation = IDLE;

	m_player.gunDelay = 0;			//�ѵ�����

	m_player.nowCharacter = RIDER;

	m_player.life = true;
	m_player.dash = false;
	m_player.melee = false;
	m_player.hit = false;
	m_player.run = false;	//


	m_player.meleeAtk = false;		//�������� ��Ʈ����Ȯ��
	m_player.meleeAtkOnce = false;	//��Ʈ���� �ѹ�������
	m_player.die = false;		//ĳ���� ���� �ִϸ��̼� �Ŀ� ��¥�װԸ���°�

	m_player.img->setFrameY(4);		//4���� IDLE �ִϸ��̼���

									//ü�¹�
	hpBar = new characterProgressBar;
	hpBar->init("ü�¹پ�", "ü�¹ٵ�", 98, 42, 172, 52);

	shieldBar = new characterProgressBar;
	shieldBar->init("����پ�", "����ٵ�", 92, 72, 158, 29);

	staminaBar = new characterProgressBar;
	staminaBar->init("���׹̳ʹپ�", "���׹̳ʹٵ�", 95, 101, 153, 6);

	hpNumDraw = new numberDrawManager;
	hpNumDraw->init("������", 3);

	shieldNumDraw = new numberDrawManager;
	shieldNumDraw->init("������", 2);

	return S_OK;
}

void rider::release()
{
	SAFE_DELETE(hpBar);
	SAFE_DELETE(shieldBar);
	SAFE_DELETE(staminaBar);
	SAFE_DELETE(hpNumDraw);
	SAFE_DELETE(shieldNumDraw);
}

void rider::update(POINT pt)
{
	//���α׷�����
	hpBar->setGauge(m_player.currentHP, m_player.maxHP);
	hpBar->update();

	hpNumDraw->update(m_player.currentHP);
	shieldNumDraw->update(m_player.currentShield);


	shieldBar->setGauge(m_player.currentShield, m_player.maxShield);
	shieldBar->update();

	staminaBar->setGauge(m_player.currentStamina, m_player.maxStamina);
	staminaBar->update();

	hpFaceInfo();


	m_player.enemy_hitRc = RectMakeCenter(m_player.x, m_player.y, 34, 72);			//������ �ǰݴ��ϴ� ��Ʈ���� x,y�������� ����
	m_player.wall_hitRc = RectMakeCenter(m_player.x, m_player.y + 32, 56, 22);		//���� �ε����� ��Ʈ����

	move();			//�̵���ɿ� ���� �Լ�

	command();		//Ŀ�ǵ� (�θ�Ŭ���������� ����Ÿ�� �뽬�� �����)


	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && !m_player.dash)	//�뽬���� �ƴϰ� Ŭ���� ���̾�
	{
		//m_player.currentHP -= 1;		//�׽�Ʈ��
		//m_player.currentShield -= 1;	//�׽�Ʈ��
		fire();
	}
	melee(pt);	//��������
	
	run();		//�޸���

	hit();		//�ǰ�

	dead();		//���

	animation();	//�ִϸ��̼� �Լ�

}

void rider::render(POINT pt)
{
	//���α׷��� ��
	hpBar->render();
	shieldBar->render();
	staminaBar->render();
	hpNumDraw->render(200, 45, 1);
	shieldNumDraw->render(210, 75, 1);
	m_player.faceImg->frameRender(getMemDC(), 1, 16);


	m_player.img->frameRender(getMemDC(), m_player.enemy_hitRc.left - 38 - pt.x, m_player.enemy_hitRc.top - 30 - pt.y);	

	HBRUSH MyBrush, OldBrush;
	HPEN MyPen, OldPen;

	MyBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 255));		//������ ��Ʈ����
	OldBrush = (HBRUSH)SelectObject(getMemDC(), MyBrush);
	MyPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	OldPen = (HPEN)SelectObject(getMemDC(), MyPen);

	Rectangle(getMemDC(), m_player.enemy_hitRc.left - pt.x, m_player.enemy_hitRc.top - pt.y,
		m_player.enemy_hitRc.right - pt.x, m_player.enemy_hitRc.bottom - pt.y);
	Rectangle(getMemDC(), m_player.wall_hitRc.left - pt.x, m_player.wall_hitRc.top - pt.y,
		m_player.wall_hitRc.right - pt.x, m_player.wall_hitRc.bottom - pt.y);

	SelectObject(getMemDC(), OldBrush);
	SelectObject(getMemDC(), OldPen);
	DeleteObject(MyPen);
	TextOut(getMemDC(), m_player.x, m_player.y - 100, _str, lstrlen(_str));		//�ؽ�Ʈ ��¿�
	TCHAR str[128];
	switch (m_player.nowCharacter)		//nowCharcher �� ����ĳ���͸� �˷���
	{
	case JIMMY:
		wsprintf(str, TEXT("���� ĳ���� : ����"));
		break;
	case RIDER:
		wsprintf(str, TEXT("���� ĳ���� : ���̴�"));
		break;
	}
	sprintf(str, TEXT("%f"), m_player.angle);
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, str, lstrlen(str));

	LineMake(getMemDC(), m_player.x, m_player.y, m_player.x + cosf(m_player.angle) * 100, m_player.y + (-sinf(m_player.angle) * 100));

	sprintf(str, TEXT("x : %f, y : %f"), m_player.x, m_player.y);
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2 + 40, str, lstrlen(str));
}

void rider::animation()
{
	//���� �÷��̿��� �ִϸ��̼� enum������ ���� �ִϸ��̼��������

	//�÷��̾� �뽬 �ִϸ��̼�
	if (m_player.animation == DASH)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 1) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 8 : m_player.frameY = 0;
		
	}

	//�÷��̾� ��� �ִϸ��̼�
	if (m_player.animation == DEATH)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 10) m_player.frameX = 0;

			if (m_player.frameX == 10)	//     �׾����� �����������ӿ� ���޽� ��¥��������
			{
				m_player.die = true;
			}
		}
		m_player.isLeft ? m_player.frameY = 9 : m_player.frameY = 1;
		
	}

	//�÷��̾� ���ı� �ִϸ��̼�
	if (m_player.animation == DIG)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 2) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 10 : m_player.frameY = 2;
	}

	//�÷��̾� �ǰ� �ִϸ��̼�
	if (m_player.animation == HIT)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 1) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 11 : m_player.frameY = 3;
	}

	//�÷��̾� �⺻ �ִϸ��̼�
	if (m_player.animation == IDLE)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 23) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 12 : m_player.frameY = 4;
	}

	//�÷��̾� �������� �ִϸ��̼�
	if (m_player.animation == MELEE)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 6) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 13 : m_player.frameY = 5;
	}

	//�÷��̾� �ڸ���Ʈ �ִϸ��̼�
	if (m_player.animation == TELEPORT)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 8) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 14 : m_player.frameY = 6;
	}

	//�÷��̾� �ȱ� �ִϸ��̼�
	if (m_player.animation == WALK)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 7) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 15 : m_player.frameY = 7;
	}

	m_player.img->setFrameX(m_player.frameX);		//�����Ӱ��� �ٲ��� X
	m_player.img->setFrameY(m_player.frameY);		//�����Ӱ��� �ٲ��� Y

}

void rider::move()
{
	//���콺���� Ŀ���ų� �۾����� �¿� ���� �ٲ�
	if (ptMouse.x < WINSIZEX / 2)m_player.isLeft = true;
	else m_player.isLeft = false;

	if (KEYMANAGER->isStayKeyDown('A') && !m_player.melee)
	{
		m_player.x -= m_player.speed;
		if (!m_player.dash && !m_player.hit) m_player.animation = WALK;

	}
	if (KEYMANAGER->isStayKeyDown('D') && !m_player.melee)
	{
		m_player.x += m_player.speed;
		if (!m_player.dash && !m_player.hit) m_player.animation = WALK;
	}
	if (KEYMANAGER->isStayKeyDown('W') && !m_player.melee)
	{
		m_player.y -= m_player.speed;
		if (!m_player.dash && !m_player.hit) m_player.animation = WALK;
	}
	if (KEYMANAGER->isStayKeyDown('S') && !m_player.melee)
	{
		m_player.y += m_player.speed;
		if (!m_player.dash && !m_player.hit) m_player.animation = WALK;
	}
	if (!KEYMANAGER->isStayKeyDown('A') &&
		!KEYMANAGER->isStayKeyDown('D') &&
		!KEYMANAGER->isStayKeyDown('W') &&
		!KEYMANAGER->isStayKeyDown('S') &&
		!m_player.dash && !m_player.hit &&
		!m_player.melee)
	{
		m_player.animation = IDLE;
	}
	//�ƹ��͵� ������ �ʾ����� �⺻ �ִϸ��̼����� ����
}

void rider::melee(POINT pt)
{
	float endX = (float)ptMouse.x;
	float endY = (float)ptMouse.y;

	if (KEYMANAGER->isOnceKeyDown('V') && !m_player.melee)		
	{
		m_player.angle = getAngle(m_player.x, m_player.y, (float)ptMouse.x, (float)ptMouse.y);
		m_player.melee = true;
		m_player.frameX = 0;

	}

	if (m_player.melee)
	{
		if (count >20)
		{
			m_player.x += cosf(m_player.angle) * m_player.speed;
			m_player.y += -sinf(m_player.angle) * m_player.speed;
		}
		m_player.animation = MELEE;
		count++;
		if (count % 35 == 0)
		{
			m_player.melee = false;
			count = 0;
		}
	}
}

void rider::hit()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		m_player.hit = true;

		m_player.animation = HIT;
	}
	if (m_player.hit)
	{
		number++;
		if (number % 17 == 0) m_player.hit = false;
	}
}

void rider::dead()
{
	if (m_player.currentHP <= 0 || KEYMANAGER->isOnceKeyDown('2'))
	{
		m_player.life = false;
	}
	if (!m_player.life)
	{
		m_player.animation = DEATH;
	}
}

void rider::fire()
{
}

void rider::hpFaceInfo()
{
	if ((m_player.maxHP / 3) * 2 < m_player.currentHP)
	{
		m_player.faceImg->setFrameX(0);
	}
	else if (m_player.maxHP / 3 < m_player.currentHP)
	{
		m_player.faceImg->setFrameX(1);
	}
	else if (m_player.maxHP / 3 > m_player.currentHP)
	{
		m_player.faceImg->setFrameX(2);
	}
}

void rider::run()
{
	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT) && !m_player.melee && !m_player.dash)
	{
		if (m_player.currentStamina > 0)	//���׹̳ʰ� 0���� ������� �޸������
		{
			m_player.run = true;
		}
		else          //�ƴϸ� �޸��� ����
		{
			m_player.run = false;
			m_player.speed = 5.0f;	//���������� ����
		}

		if (m_player.run)
		{
			m_player.animation = RUN;
			m_player.speed = 7.5f;	//�̵��ӵ� 50%����
			runDelay++;
			if (runDelay % 2 == 0)
			{
				m_player.currentStamina--;	//�޸��� ���׹̳ʰ���
			}
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LSHIFT))	//����ƮŰ�� ���� �޸�������
	{
		m_player.run = false;
		m_player.speed = 5.0f;
	}
	if (m_player.currentStamina < 100 && !m_player.run)	//���׹̳ʰ� 100���� �۰� �޸������� �ƴ϶��
	{
		runDelay++;
		if (runDelay % 3 == 0)
		{
			m_player.currentStamina++;	//���׹̳� ȸ��
		}
	}
}
