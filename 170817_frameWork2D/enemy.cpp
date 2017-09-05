#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

HRESULT enemy::init(POINT position)
{
	return E_NOTIMPL;
}

void enemy::release()
{
}

void enemy::update()
{
}

void enemy::render()
{
}

void enemy::animation()
{
}

bool enemy::dead()
{
	return false;
}

//====================================================================	거북이
turtle::turtle()
{
}

turtle::~turtle()
{
}

HRESULT turtle::init(POINT position)
{
	ZeroMemory(&m_enemy, sizeof(m_enemy));
	
	m_enemy.image = IMAGEMANAGER->findImage("거북이");
	m_enemy.x = position.x;
	m_enemy.y = position.y;
	m_enemy.rc = RectMakeCenter(m_enemy.x, m_enemy.y, 42, 64);																					//에너미 렉트
	m_enemy.detection = RectMakeCenter((m_enemy.rc.left + m_enemy.rc.right) / 2, (m_enemy.rc.top + m_enemy.rc.bottom) / 2, 500, 500);			//에너미 탐지 거리
	m_enemy.currentHP = m_enemy.maxHP = 50;																										//현재 HP / 최대 HP
	m_enemy.speed = 3.0f;																														//에너미 이동 속도
	m_enemy.count = m_enemy.currentFrameX = m_enemy.currentFrameY = 0;
	m_enemy.isDetection = false;																												//플레이어를 탐지 했냐?
	m_enemy.current = STOP_ENEMY;																												//에너미 현재 상태
	m_enemy.isLeft = true;																														//에너미가 왼쪽을 보고 있냐?

	//프로그레스바
	m_progressBar = new progressBar;
	m_progressBar->init("Images/hpBar_front.bmp", "Images/hpBar_back.bmp", m_enemy.image->getX() - 30, m_enemy.image->getY() - 60, 61, 7);

	return S_OK;
}

void turtle::release()
{
}

void turtle::update()
{
	m_enemy.rc = RectMakeCenter(m_enemy.x, m_enemy.y, 42, 64);
	m_enemy.detection = RectMakeCenter((m_enemy.rc.left + m_enemy.rc.right) / 2, (m_enemy.rc.top + m_enemy.rc.bottom) / 2, 500, 500);

	animation();

	//프로그레스바
	m_progressBar->setX(m_enemy.image->getX() - 30);
	m_progressBar->setY(m_enemy.image->getY() - 60);
	m_progressBar->setGauge(m_enemy.currentHP, m_enemy.maxHP);
	m_progressBar->update();
}

void turtle::render()
{
	//Rectangle(getMemDC(), m_enemy.detection.left, m_enemy.detection.top, m_enemy.detection.right, m_enemy.detection.bottom);
	//Rectangle(getMemDC(), m_enemy.rc.left, m_enemy.rc.top, m_enemy.rc.right, m_enemy.rc.bottom);
	m_enemy.image->frameRender(getMemDC(), m_enemy.rc.left - 36, m_enemy.rc.top - 26, m_enemy.currentFrameX, m_enemy.currentFrameY);
	m_progressBar->render();
}

void turtle::animation()
{
	//거북이 기본 자세
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
	//거북이 이동 자세
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
	//거북이 피격 자세
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
	//거북이 죽음
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


//====================================================================	오리
duck::duck()
{
}

duck::~duck()
{
}

HRESULT duck::init(POINT position)
{
	ZeroMemory(&m_enemy, sizeof(m_enemy));

	m_enemy.image = IMAGEMANAGER->findImage("오리");
	m_enemy.x = position.x;
	m_enemy.y = position.y;
	m_enemy.rc = RectMakeCenter(m_enemy.x, m_enemy.y, 38, 60);																					//에너미 렉트
	m_enemy.detection = RectMakeCenter((m_enemy.rc.left + m_enemy.rc.right) / 2, (m_enemy.rc.top + m_enemy.rc.bottom) / 2, 500, 500);			//에너미 탐지 거리
	m_enemy.currentHP = m_enemy.maxHP = 100;																									//현재 HP / 최대 HP
	m_enemy.dashCoolTime = 0;																													//에너미 대쉬 쿨타임
	m_enemy.dashCoolTimeMax = RND->getIntFromInto(150, 250);																					//에너미 대쉬 쿨타임 맥스
	m_enemy.dash = 15.0f;																														//에너미 대쉬 속도
	m_enemy.acceleration = 0;																													//에너미 대쉬 감속
	m_enemy.speed = 3.0f;																														//에너미 이동 속도
	m_enemy.count = m_enemy.currentFrameX = m_enemy.currentFrameY = 0;
	m_enemy.isDetection = false;																												//플레이어를 탐지 했냐?
	m_enemy.current = STOP_ENEMY;																												//에너미 현재 상태
	m_enemy.isLeft = true;																														//에너미가 왼쪽을 보고 있냐?
	m_enemy.angle = RND->getFloat(360.0f);

	//프로그레스바
	m_progressBar = new progressBar;
	m_progressBar->init("Images/hpBar_front.bmp", "Images/hpBar_back.bmp", m_enemy.image->getX() - 30, m_enemy.image->getY() - 60, 61, 7);

	return S_OK;
}

void duck::release()
{
}

void duck::update()
{
	m_enemy.rc = RectMakeCenter(m_enemy.x, m_enemy.y, 38, 60);
	m_enemy.detection = RectMakeCenter((m_enemy.rc.left + m_enemy.rc.right) / 2, (m_enemy.rc.top + m_enemy.rc.bottom) / 2, 500, 500);

	animation();
	dashCoolTime();
	dash();

	//프로그레스바
	m_progressBar->setX(m_enemy.image->getX() - 30);
	m_progressBar->setY(m_enemy.image->getY() - 60);
	m_progressBar->setGauge(m_enemy.currentHP, m_enemy.maxHP);
	m_progressBar->update();
}

void duck::render()
{
	//Rectangle(getMemDC(), m_enemy.detection.left, m_enemy.detection.top, m_enemy.detection.right, m_enemy.detection.bottom);
	//Rectangle(getMemDC(), m_enemy.rc.left, m_enemy.rc.top, m_enemy.rc.right, m_enemy.rc.bottom);
	m_enemy.image->frameRender(getMemDC(), m_enemy.rc.left - 38, m_enemy.rc.top - 30, m_enemy.currentFrameX, m_enemy.currentFrameY);
	m_progressBar->render();
}

void duck::animation()
{
	//오리 기본 자세
	if (m_enemy.current == STOP_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 6) m_enemy.currentFrameX = 0;
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 0 : m_enemy.currentFrameY = 4;
	}
	//오리 이동 자세
	if (m_enemy.current == MOVE_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 12) m_enemy.currentFrameX = 0;
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 1 : m_enemy.currentFrameY = 5;
	}
	//오리 피격 자세
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
	//오리 대쉬
	if (m_enemy.current == DASH_ENEMY)
	{
		m_enemy.x += cosf(m_enemy.angle) * m_enemy.dash;
		m_enemy.y += (-sinf(m_enemy.angle)) * m_enemy.dash;
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
		m_enemy.angle = RND->getFloat(360.0f);
	}
	return false;
}

bool duck::dead()
{
	//오리 죽음
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
		m_enemy.isLeft ? m_enemy.currentFrameY = 3 : m_enemy.currentFrameY = 7;
	}
	return false;
}


//====================================================================	가미가제
kamikaze::kamikaze()
{
}

kamikaze::~kamikaze()
{
}

HRESULT kamikaze::init(POINT position)
{
	ZeroMemory(&m_enemy, sizeof(m_enemy));

	m_enemy.image = IMAGEMANAGER->findImage("가미가제");
	m_enemy.x = position.x;
	m_enemy.y = position.y;
	m_enemy.rc = RectMakeCenter(m_enemy.x, m_enemy.y, 38, 38);																					//에너미 렉트
	m_enemy.detection = RectMakeCenter((m_enemy.rc.left + m_enemy.rc.right) / 2, (m_enemy.rc.top + m_enemy.rc.bottom) / 2, 500, 500);			//에너미 탐지 거리
	m_enemy.currentHP = m_enemy.maxHP = 35;																										//현재 HP / 최대 HP
	m_enemy.dashCoolTime = 0;																													//에너미 대쉬 쿨타임
	m_enemy.dashCoolTimeMax = RND->getIntFromInto(100, 200);																					//에너미 대쉬 쿨타임 맥스
	m_enemy.dash = 20.0f;																														//에너미 대쉬 속도
	m_enemy.acceleration = 0;																													//에너미 대쉬 감속
	m_enemy.speed = 3.0f;																														//에너미 이동 속도
	m_enemy.count = m_enemy.currentFrameX = m_enemy.currentFrameY = 0;
	m_enemy.isDetection = false;																												//플레이어를 탐지 했냐?
	m_enemy.current = STOP_ENEMY;																												//에너미 현재 상태
	m_enemy.isLeft = true;																														//에너미가 왼쪽을 보고 있냐?
	m_enemy.angle = RND->getFloat(360.0f);

	//프로그레스바
	m_progressBar = new progressBar;
	m_progressBar->init("Images/hpBar_front.bmp", "Images/hpBar_back.bmp", m_enemy.image->getX(), m_enemy.image->getY() - 30, 61, 7);

	return S_OK;
}

void kamikaze::release()
{
}

void kamikaze::update()
{
	m_enemy.rc = RectMakeCenter(m_enemy.x, m_enemy.y, 38, 38);
	m_enemy.detection = RectMakeCenter((m_enemy.rc.left + m_enemy.rc.right) / 2, (m_enemy.rc.top + m_enemy.rc.bottom) / 2, 500, 500);

	animation();
	dashCoolTime();
	dash();

	//프로그레스바
	m_progressBar->setX(m_enemy.image->getX() - 30);
	m_progressBar->setY(m_enemy.image->getY() - 50);
	m_progressBar->setGauge(m_enemy.currentHP, m_enemy.maxHP);
	m_progressBar->update();
}

void kamikaze::render()
{
	//Rectangle(getMemDC(), m_enemy.detection.left, m_enemy.detection.top, m_enemy.detection.right, m_enemy.detection.bottom);
	//Rectangle(getMemDC(), m_enemy.rc.left, m_enemy.rc.top, m_enemy.rc.right, m_enemy.rc.bottom);
	m_enemy.image->frameRender(getMemDC(), m_enemy.rc.left - 37, m_enemy.rc.top - 51, m_enemy.currentFrameX, m_enemy.currentFrameY);
	m_progressBar->render();
}

void kamikaze::animation()
{
	//가미가제 기본 자세
	if (m_enemy.current == STOP_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 15) m_enemy.currentFrameX = 0;
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 0 : m_enemy.currentFrameY = 4;
	}
	//가미가제 이동 자세
	if (m_enemy.current == MOVE_ENEMY)
	{
		m_enemy.count++;
		if (m_enemy.count % 5 == 0)
		{
			m_enemy.count = 0;
			m_enemy.currentFrameX++;
			if (m_enemy.currentFrameX > 7) m_enemy.currentFrameX = 0;
		}
		m_enemy.isLeft ? m_enemy.currentFrameY = 1 : m_enemy.currentFrameY = 5;
	}
	//가미가제 피격 자세
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
	//가미가제 대쉬
	if (m_enemy.current == DASH_ENEMY)
	{
		m_enemy.x += cosf(m_enemy.angle) * m_enemy.dash;
		m_enemy.y += (-sinf(m_enemy.angle)) * m_enemy.dash;
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
		m_enemy.angle = RND->getFloat(360.0f);
	}
	return false;
}

bool kamikaze::dead()
{
	//가미가제 죽음
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
		m_enemy.isLeft ? m_enemy.currentFrameY = 3 : m_enemy.currentFrameY = 7;
	}
	return false;
}
