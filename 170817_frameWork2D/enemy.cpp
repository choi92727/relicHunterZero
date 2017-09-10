#include "stdafx.h"
#include "enemy.h"

#include "gunInterface.h"
#include "defaultGun.h"
#include "bulletManager.h"


enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init(POINT position)
{
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
}

void enemy::render(POINT pt)
{
}

void enemy::detection()
{
}

void enemy::animation()
{
}

void enemy::dashCoolTime()
{
}

bool enemy::dead()
{
	return false;
}

bool enemy::dash()
{
	return false;
}

bool enemy::fireCheck()
{
	return false;
}

//====================================================================	�ź���
turtle::turtle()
{
}

turtle::~turtle()
{
}

HRESULT turtle::init(POINT position)
{
	ZeroMemory(&m_enemy, sizeof(m_enemy));
	
	m_enemy.image = IMAGEMANAGER->findImage("�ź���");
	m_enemy.x = position.x;
	m_enemy.y = position.y;
	m_enemy.rc = RectMakeCenter(m_enemy.x, m_enemy.y, 42, 64);																					//���ʹ� ��Ʈ
	m_enemy.detectionRc = RectMakeCenter((m_enemy.rc.left + m_enemy.rc.right) / 2, (m_enemy.rc.top + m_enemy.rc.bottom) / 2, 500, 500);			//���ʹ� Ž�� �Ÿ�
	m_enemy.currentHP = m_enemy.maxHP = 50;																										//���� HP / �ִ� HP
	m_enemy.speed = 3.0f;																														//���ʹ� �̵� �ӵ�
	m_enemy.count = m_enemy.detectionCount = 0;
	m_enemy.currentFrameX = RND->getInt(11);
	m_enemy.currentFrameY = 0;
	m_enemy.detectionX = 0;
	m_enemy.isDetection = m_enemy.detection = false;																							//�÷��̾ Ž�� �߳�?
	m_enemy.current = STOP_ENEMY;																												//���ʹ� ���� ����
	m_enemy.isLeft = true;																														//���ʹ̰� ������ ���� �ֳ�?
	m_enemy.collisionRc = RectMakeCenter(m_enemy.x, m_enemy.y + 30, 42, 5);
	//�߰� ����->������
	m_enemy.fire = true;
	m_enemy.fireDelay= 1.5f * 60.0f;//�Ѿ� �߻� ���ð�
	m_enemy.fireEnemy = true;//���� ��� ���ʹ�����
	m_enemy.enemyNumber = 0;//���� ���ʹ��� ���ڰ�

	//���α׷�����
	m_progressBar = new progressBar;
	m_progressBar->init("Images/hpBar_front.bmp", "Images/hpBar_back.bmp", m_enemy.x - 30, m_enemy.y - 60, 61, 7);

	return S_OK;
}

void turtle::release()
{
	SAFE_DELETE(m_progressBar);
}

void turtle::update()
{



	m_enemy.rc = RectMakeCenter(m_enemy.x, m_enemy.y, 42, 64);
	m_enemy.detectionRc = RectMakeCenter((m_enemy.rc.left + m_enemy.rc.right) / 2, (m_enemy.rc.top + m_enemy.rc.bottom) / 2, 500, 500);

	detection();
	animation();
	//fireCheck();
	m_enemy.collisionRc = RectMakeCenter(m_enemy.x, m_enemy.y + 30, 42, 5);
	//���α׷�����
	m_progressBar->setX(m_enemy.x - 30);
	m_progressBar->setY(m_enemy.y - 60);
	m_progressBar->setGauge(m_enemy.currentHP, m_enemy.maxHP);
	m_progressBar->update();

	//�Լ� ���۵����� ���⿡�� �ٿ�����
	//if (m_enemy.fire)
	//{
	//	
	//}
	//else
	//{
	//	m_enemy.fireDelay -= 1.0f;
	//	if (m_enemy.fireDelay <= 0)
	//	{
	//		m_enemy.fire = true;
	//		m_enemy.fireDelay = 1.5f * 60.0f;
	//	}
	//}
}

void turtle::render(POINT pt)
{
	//Rectangle(getMemDC(), m_enemy.detectionRc.left, m_enemy.detectionRc.top, m_enemy.detectionRc.right, m_enemy.detectionRc.bottom);
	//Rectangle(getMemDC(), m_enemy.rc.left, m_enemy.rc.top, m_enemy.rc.right, m_enemy.rc.bottom);

	m_enemy.image->frameRender(getMemDC(), m_enemy.rc.left - 36 - pt.x, m_enemy.rc.top - 26 - pt.y, m_enemy.currentFrameX, m_enemy.currentFrameY);
	if(m_enemy.isDetection && !m_enemy.detection) IMAGEMANAGER->frameRender("���ʹ�_Ž��", getMemDC(), m_enemy.x - 8 - pt.x, m_enemy.y - 40 - pt.y, m_enemy.detectionX, 0);

	//m_enemy.image->frameRender(getMemDC(), m_enemy.rc.left - 36, m_enemy.rc.top - 26, m_enemy.currentFrameX, m_enemy.currentFrameY);
	//if (m_enemy.isDetection && !m_enemy.detection) IMAGEMANAGER->frameRender("���ʹ�_Ž��", getMemDC(), m_enemy.x - 8, m_enemy.y - 40, m_enemy.detectionX, 0);

	m_progressBar->render(pt);

	char text[64];
	wsprintf(text, "%d", m_enemy.fireDelay);
	TextOut(getMemDC(), m_enemy.rc.left - 36 - pt.x,m_enemy.rc.top - 26 - pt.y,text,strlen(text));


}

void turtle::detection()
{
	if (m_enemy.isDetection)
	{
		m_enemy.detectionCount++;
		if (m_enemy.detectionCount % 5 == 0)
		{
			m_enemy.detectionCount = 0;
			m_enemy.detectionX++;
			if (m_enemy.detectionX > IMAGEMANAGER->findImage("���ʹ�_Ž��")->getMaxFrameX()) m_enemy.detection = true;
		}
	}
}

void turtle::animation()
{
	//�ź��� �⺻ �ڼ�
	if (m_enemy.current == STOP_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 11) m_enemy.currentFrameX = 0;
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 0 : m_enemy.currentFrameY = 4;
	}
	//�ź��� �̵� �ڼ�
	if (m_enemy.current == MOVE_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 5) m_enemy.currentFrameX = 0;
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 1 : m_enemy.currentFrameY = 5;
	}
	//�ź��� �ǰ� �ڼ�
	if (m_enemy.current == HIT_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 1)
			{
				m_enemy.currentFrameX = 0;
				m_enemy.current = STOP_ENEMY;
			}
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 2 : m_enemy.currentFrameY = 6;
	}
}

bool turtle::dead()
{
	//�ź��� ����
	if (m_enemy.current == DEAD_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 13)
			{
				m_enemy.currentFrameX = 0;
				return true;
			}
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 3 : m_enemy.currentFrameY = 7;
	}
	return false;
}

bool turtle::fireCheck()
{
	return true;
}


//====================================================================	����
duck::duck()
{
}

duck::~duck()
{
}

HRESULT duck::init(POINT position)
{
	ZeroMemory(&m_enemy, sizeof(m_enemy));

	m_enemy.image = IMAGEMANAGER->findImage("����");
	m_enemy.x = position.x;
	m_enemy.y = position.y;
	m_enemy.rc = RectMakeCenter(m_enemy.x, m_enemy.y, 38, 60);																					//���ʹ� ��Ʈ
	m_enemy.detectionRc = RectMakeCenter((m_enemy.rc.left + m_enemy.rc.right) / 2, (m_enemy.rc.top + m_enemy.rc.bottom) / 2, 500, 500);			//���ʹ� Ž�� �Ÿ�
	m_enemy.collisionRc = RectMakeCenter(m_enemy.x, m_enemy.y + 28, 38, 5);
	m_enemy.currentHP = m_enemy.maxHP = 100;																									//���� HP / �ִ� HP
	m_enemy.dashCoolTime = 0;																													//���ʹ� �뽬 ��Ÿ��
	m_enemy.dashCoolTimeMax = RND->getIntFromInto(150, 250);																					//���ʹ� �뽬 ��Ÿ�� �ƽ�
	m_enemy.dash = 15.0f;																														//���ʹ� �뽬 �ӵ�
	m_enemy.acceleration = 0;																													//���ʹ� �뽬 ����
	m_enemy.speed = 3.0f;																														//���ʹ� �̵� �ӵ�
	m_enemy.count = m_enemy.detectionCount = 0;
	m_enemy.currentFrameX = RND->getInt(6);
	m_enemy.currentFrameY = 0;
	m_enemy.detectionX = 0;
	m_enemy.isDetection = m_enemy.detection = false;																							//�÷��̾ Ž�� �߳�?
	m_enemy.current = STOP_ENEMY;																												//���ʹ� ���� ����
	m_enemy.isLeft = true;																														//���ʹ̰� ������ ���� �ֳ�?
	//m_enemy.angle = RND->getFloat(360.0f);
	//�߰� ����
	m_enemy.fire = true;
	m_enemy.fireDelay = 1.0f * 60.0f;//�Ѿ� �߻� ���ð�
	m_enemy.fireEnemy = true;//���� ��� ���ʹ�����
	m_enemy.enemyNumber = 0;//���� ���ʹ��� ���ڰ�


	//���α׷�����
	m_progressBar = new progressBar;
	m_progressBar->init("Images/hpBar_front.bmp", "Images/hpBar_back.bmp", m_enemy.x - 30, m_enemy.y - 60, 61, 7);

	return S_OK;
}

void duck::release()
{
	SAFE_DELETE(m_progressBar);
}

void duck::update()
{
	m_enemy.rc = RectMakeCenter(m_enemy.x, m_enemy.y, 38, 60);
	m_enemy.detectionRc = RectMakeCenter((m_enemy.rc.left + m_enemy.rc.right) / 2, (m_enemy.rc.top + m_enemy.rc.bottom) / 2, 500, 500);
	m_enemy.collisionRc = RectMakeCenter(m_enemy.x, m_enemy.y + 28, 38, 5);
	detection();
	animation();
	if(m_enemy.isDetection) dashCoolTime();
	dash();

	//���α׷�����
	m_progressBar->setX(m_enemy.x - 30);
	m_progressBar->setY(m_enemy.y - 60);
	m_progressBar->setGauge(m_enemy.currentHP, m_enemy.maxHP);
	m_progressBar->update();
}

void duck::render(POINT pt)
{
	//Rectangle(getMemDC(), m_enemy.detectionRc.left, m_enemy.detectionRc.top, m_enemy.detectionRc.right, m_enemy.detectionRc.bottom);
	//Rectangle(getMemDC(), m_enemy.rc.left, m_enemy.rc.top, m_enemy.rc.right, m_enemy.rc.bottom);

	m_enemy.image->frameRender(getMemDC(), m_enemy.rc.left - 38 - pt.x, m_enemy.rc.top - 30 - pt.y, m_enemy.currentFrameX, m_enemy.currentFrameY);
	if (m_enemy.isDetection && !m_enemy.detection) IMAGEMANAGER->frameRender("���ʹ�_Ž��", getMemDC(), m_enemy.x - 8 - pt.x, m_enemy.y - 40 - pt.y, m_enemy.detectionX, 0);

	//m_enemy.image->frameRender(getMemDC(), m_enemy.rc.left - 38, m_enemy.rc.top - 30, m_enemy.currentFrameX, m_enemy.currentFrameY);
	//if (m_enemy.isDetection && !m_enemy.detection) IMAGEMANAGER->frameRender("���ʹ�_Ž��", getMemDC(), m_enemy.x - 8, m_enemy.y - 40, m_enemy.detectionX, 0);

	m_progressBar->render(pt);
}

void duck::detection()
{
	if (m_enemy.isDetection)
	{
		m_enemy.detectionCount++;
		if (m_enemy.detectionCount % 5 == 0)
		{
			m_enemy.detectionCount = 0;
			m_enemy.detectionX++;
			if (m_enemy.detectionX > IMAGEMANAGER->findImage("���ʹ�_Ž��")->getMaxFrameX()) m_enemy.detection = true;
		}
	}
}

void duck::animation()
{
	//���� �⺻ �ڼ�
	if (m_enemy.current == STOP_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 6) m_enemy.currentFrameX = 0;
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 0 : m_enemy.currentFrameY = 5;
	}
	//���� �̵� �ڼ�
	if (m_enemy.current == MOVE_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 12) m_enemy.currentFrameX = 0;
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 1 : m_enemy.currentFrameY = 6;
	}
	//���� �ǰ� �ڼ�
	if (m_enemy.current == HIT_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 1)
			{
				m_enemy.currentFrameX = 0;
				m_enemy.current = STOP_ENEMY;
			}
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 2 : m_enemy.currentFrameY = 7;
	}
}

void duck::dashCoolTime()
{
	if (m_enemy.current != HIT_ENEMY &&m_enemy.current != DASH_ENEMY && m_enemy.current != DEAD_ENEMY)
	{
		m_enemy.dashCoolTime++;
		if (m_enemy.dashCoolTime >= m_enemy.dashCoolTimeMax)
		{
			m_enemy.dashCoolTime = 0;
			m_enemy.dashCoolTimeMax = RND->getIntFromInto(150, 250);
			m_enemy.current = DASH_ENEMY;
		}
	}
}

bool duck::dash()
{
	//���� �뽬
	if (m_enemy.current == DASH_ENEMY)
	{
		m_enemy.x += cosf(m_enemy.dashAngle) * m_enemy.dash;
		m_enemy.y += (-sinf(m_enemy.dashAngle)) * m_enemy.dash;
		m_enemy.acceleration += 0.025f;
		m_enemy.dash -= m_enemy.acceleration;
		m_enemy.currentFrameX = 0;
		if (m_enemy.dash <= 0)
		{
			m_enemy.current = STOP_ENEMY;
			return true;
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 4 : m_enemy.currentFrameY = 9;
	}
	else
	{
		m_enemy.dash = 10.0f;
		m_enemy.acceleration = 0;
		m_enemy.dashAngle = RND->getFloat(360.0f);
	}
	return false;
}

bool duck::dead()
{
	//���� ����
	if (m_enemy.current == DEAD_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 10)
			{
				m_enemy.currentFrameX = 0;
				return true;
			}
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 3 : m_enemy.currentFrameY = 8;
	}
	return false;
}


//====================================================================	���̰���
kamikaze::kamikaze()
{
}

kamikaze::~kamikaze()
{
}

HRESULT kamikaze::init(POINT position)
{
	ZeroMemory(&m_enemy, sizeof(m_enemy));

	m_enemy.image = IMAGEMANAGER->findImage("���̰���");
	m_enemy.x = position.x;
	m_enemy.y = position.y;
	m_enemy.rc = RectMakeCenter(m_enemy.x, m_enemy.y, 38, 38);																					//���ʹ� ��Ʈ
	m_enemy.detectionRc = RectMakeCenter((m_enemy.rc.left + m_enemy.rc.right) / 2, (m_enemy.rc.top + m_enemy.rc.bottom) / 2, 500, 500);			//���ʹ� Ž�� �Ÿ�
	m_enemy.collisionRc = RectMakeCenter(m_enemy.x, m_enemy.y + 20, 38, 5);
	m_enemy.currentHP = m_enemy.maxHP = 35;																										//���� HP / �ִ� HP
	m_enemy.dashCoolTime = 0;																													//���ʹ� �뽬 ��Ÿ��
	m_enemy.dashCoolTimeMax = RND->getIntFromInto(100, 200);																					//���ʹ� �뽬 ��Ÿ�� �ƽ�
	m_enemy.dash = 20.0f;																														//���ʹ� �뽬 �ӵ�
	m_enemy.acceleration = 0;																													//���ʹ� �뽬 ����
	m_enemy.speed = 3.0f;																														//���ʹ� �̵� �ӵ�
	m_enemy.count = m_enemy.detectionCount = 0;
	m_enemy.currentFrameX = RND->getInt(15);
	m_enemy.currentFrameY = 0;
	m_enemy.detectionX = 0;
	m_enemy.isDetection = m_enemy.detection = false;																							//�÷��̾ Ž�� �߳�?
	m_enemy.current = STOP_ENEMY;																												//���ʹ� ���� ����
	m_enemy.isLeft = true;																														//���ʹ̰� ������ ���� �ֳ�?
	//m_enemy.angle = RND->getFloat(360.0f);

	m_enemy.fire = false;
	m_enemy.fireDelay = 1.0f * 60.0f;//�Ѿ� �߻� ���ð�
	m_enemy.fireEnemy = true;//���� ��� ���ʹ�����
	m_enemy.enemyNumber = 0;//���� ���ʹ��� ���ڰ�

	//���α׷�����
	m_progressBar = new progressBar;
	m_progressBar->init("Images/hpBar_front.bmp", "Images/hpBar_back.bmp", m_enemy.x - 30, m_enemy.y - 50, 61, 7);

	return S_OK;
}

void kamikaze::release()
{
	SAFE_DELETE(m_progressBar);
}

void kamikaze::update()
{
	m_enemy.rc = RectMakeCenter(m_enemy.x, m_enemy.y, 38, 38);
	m_enemy.detectionRc = RectMakeCenter((m_enemy.rc.left + m_enemy.rc.right) / 2, (m_enemy.rc.top + m_enemy.rc.bottom) / 2, 500, 500);
	m_enemy.collisionRc = RectMakeCenter(m_enemy.x, m_enemy.y + 20, 38, 5);

	detection();
	animation();
	if (m_enemy.isDetection) dashCoolTime();
	dash();

	//���α׷�����
	m_progressBar->setX(m_enemy.x - 30);
	m_progressBar->setY(m_enemy.y - 50);
	m_progressBar->setGauge(m_enemy.currentHP, m_enemy.maxHP);
	m_progressBar->update();
}

void kamikaze::render(POINT pt)
{
	//Rectangle(getMemDC(), m_enemy.detectionRc.left, m_enemy.detectionRc.top, m_enemy.detectionRc.right, m_enemy.detectionRc.bottom);
	//Rectangle(getMemDC(), m_enemy.rc.left, m_enemy.rc.top, m_enemy.rc.right, m_enemy.rc.bottom);

	m_enemy.image->frameRender(getMemDC(), m_enemy.rc.left - 37 - pt.x, m_enemy.rc.top - 51 - pt.y, m_enemy.currentFrameX, m_enemy.currentFrameY);
	if (m_enemy.isDetection && !m_enemy.detection) IMAGEMANAGER->frameRender("���ʹ�_Ž��", getMemDC(), m_enemy.x - 8 - pt.x, m_enemy.y - 40 - pt.y, m_enemy.detectionX, 0);

	//m_enemy.image->frameRender(getMemDC(), m_enemy.rc.left - 37, m_enemy.rc.top - 51, m_enemy.currentFrameX, m_enemy.currentFrameY);
	//if (m_enemy.isDetection && !m_enemy.detection) IMAGEMANAGER->frameRender("���ʹ�_Ž��", getMemDC(), m_enemy.x - 8, m_enemy.y - 40, m_enemy.detectionX, 0);

	m_progressBar->render(pt);
}

void kamikaze::detection()
{
	if (m_enemy.isDetection)
	{
		m_enemy.detectionCount++;
		if (m_enemy.detectionCount % 5 == 0)
		{
			m_enemy.detectionCount = 0;
			m_enemy.detectionX++;
			if (m_enemy.detectionX > IMAGEMANAGER->findImage("���ʹ�_Ž��")->getMaxFrameX()) m_enemy.detection = true;
		}
	}
}

void kamikaze::animation()
{
	//���̰��� �⺻ �ڼ�
	if (m_enemy.current == STOP_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 15) m_enemy.currentFrameX = 0;
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 0 : m_enemy.currentFrameY = 5;
	}
	//���̰��� �̵� �ڼ�
	if (m_enemy.current == MOVE_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 7) m_enemy.currentFrameX = 0;
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 1 : m_enemy.currentFrameY = 6;
	}
	//���̰��� �ǰ� �ڼ�
	if (m_enemy.current == HIT_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 1)
			{
				m_enemy.currentFrameX = 0;
				m_enemy.current = STOP_ENEMY;
			}
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 2 : m_enemy.currentFrameY = 7;
	}
}

void kamikaze::dashCoolTime()
{
	if (m_enemy.current != HIT_ENEMY &&m_enemy.current != DASH_ENEMY && m_enemy.current != DEAD_ENEMY)
	{
		m_enemy.dashCoolTime++;
		if (m_enemy.dashCoolTime >= m_enemy.dashCoolTimeMax)
		{
			m_enemy.dashCoolTime = 0;
			m_enemy.dashCoolTimeMax = RND->getIntFromInto(100, 200);
			m_enemy.current = DASH_ENEMY;
		}
	}
}

bool kamikaze::dash()
{
	//���̰��� �뽬
	if (m_enemy.current == DASH_ENEMY)
	{
		m_enemy.x += cosf(m_enemy.dashAngle) * m_enemy.dash;
		m_enemy.y += (-sinf(m_enemy.dashAngle)) * m_enemy.dash;

		m_enemy.acceleration += 0.20;
		m_enemy.dash -= m_enemy.acceleration;
		m_enemy.currentFrameX = 0;
		if (m_enemy.dash <= 0)
		{
			m_enemy.current = STOP_ENEMY;
			return true;
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 4 : m_enemy.currentFrameY = 9;
	}
	else
	{
		m_enemy.dash = 20.0f;
		m_enemy.acceleration = 0;
		m_enemy.dashAngle = m_enemy.angle + RND->getFloatFromInto(-0.5f, 0.5f);
	}
	return false;
}

bool kamikaze::dead()
{
	//���̰��� ����
	if (m_enemy.current == DEAD_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 12)
			{
				m_enemy.currentFrameX = 0;
				return true;
			}
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 3 : m_enemy.currentFrameY = 8;
	}
	return false;
}
