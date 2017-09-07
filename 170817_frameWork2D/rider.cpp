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
	m_player.x = position.x;
	m_player.y = position.y;
	m_player.enemy_hitRc = RectMakeCenter(m_player.x, m_player.y, 34, 72);	//������ �ǰݰ����� ��Ʈ
	m_player.wall_hitRc = RectMakeCenter(m_player.x, m_player.y + 32, 56, 22);	//���� �ε�ġ�� ��Ʈ
	m_player.currentHP = m_player.maxHP = 100;
	m_player.currentShield = m_player.maxShield = 50;
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

	m_player.img->setFrameY(4);		//4���� IDLE �ִϸ��̼���
	return S_OK;
}

void rider::release()
{
}

void rider::update()
{
	m_player.enemy_hitRc = RectMakeCenter(m_player.x, m_player.y, 34, 72);			//������ �ǰݴ��ϴ� ��Ʈ���� x,y�������� ����
	m_player.wall_hitRc = RectMakeCenter(m_player.x, m_player.y + 32, 56, 22);		//���� �ε����� ��Ʈ����

	move();			//�̵����ɿ� ���� �Լ�
	animation();	//�ִϸ��̼� �Լ�

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && !m_player.dash)	//�뽬���� �ƴϰ� Ŭ���� ���̾�
	{
		fire();
	}
	melee();	//��������

	hit();		//�ǰ�

	dead();		//���

	command();		//Ŀ�ǵ� (�θ�Ŭ���������� ������Ÿ�� �뽬�� �����)
}

void rider::render()
{
	m_player.img->frameRender(getMemDC(), m_player.enemy_hitRc.left - 38, m_player.enemy_hitRc.top - 30);	

	HBRUSH MyBrush, OldBrush;
	HPEN MyPen, OldPen;

	MyBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 255));		//������ ��Ʈ����
	OldBrush = (HBRUSH)SelectObject(getMemDC(), MyBrush);
	MyPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	OldPen = (HPEN)SelectObject(getMemDC(), MyPen);

	Rectangle(getMemDC(), m_player.enemy_hitRc.left, m_player.enemy_hitRc.top,
		m_player.enemy_hitRc.right, m_player.enemy_hitRc.bottom);
	Rectangle(getMemDC(), m_player.wall_hitRc.left, m_player.wall_hitRc.top,
		m_player.wall_hitRc.right, m_player.wall_hitRc.bottom);

	SelectObject(getMemDC(), OldBrush);
	SelectObject(getMemDC(), OldPen);
	DeleteObject(MyPen);

	//TextOut(getMemDC(), m_player.x, m_player.y-100, _str, lstrlen(_str));
	//TCHAR str[128];
	//switch (m_player.nowCharacter)		//nowCharcher �� ����ĳ���͸� �˷���
	//{
	//case JIMMY:
	//	wsprintf(str, TEXT("���� ĳ���� : ����"));
	//	break;
	//case RIDER:
	//	wsprintf(str, TEXT("���� ĳ���� : ���̴�"));
	//	break;
	//}
	//TextOut(getMemDC(), WINSIZEX / 2, 100, str, lstrlen(str));
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
	if (ptMouse.x < m_player.x)m_player.isLeft = true;
	else m_player.isLeft = false;

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		m_player.x -= m_player.speed;
		if (!m_player.dash && !m_player.hit) m_player.animation = WALK;

	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		m_player.x += m_player.speed;
		if (!m_player.dash && !m_player.hit) m_player.animation = WALK;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		m_player.y -= m_player.speed;
		if (!m_player.dash && !m_player.hit) m_player.animation = WALK;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
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

void rider::melee()
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