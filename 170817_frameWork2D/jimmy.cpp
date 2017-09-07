#include "stdafx.h"
#include "jimmy.h"


jimmy::jimmy()
{
}


jimmy::~jimmy()
{
}

HRESULT jimmy::init(POINT position)
{

	_fCommandClear = 2.5f;	//커맨드 입력시간
	_fCommandTime = 0.0f;

	ZeroMemory(&m_player, sizeof(m_player));

	m_player.img = IMAGEMANAGER->findImage("지미");		//지미 이미지를 넣음
	m_player.x = position.x;
	m_player.y = position.y;
	m_player.enemy_hitRc = RectMakeCenter(m_player.x, m_player.y, 34, 56);	//적에게 피격가능한 렉트
	m_player.wall_hitRc = RectMakeCenter(m_player.x, m_player.y+22, 34, 21);	//벽에 부딪치는 렉트
	m_player.currentHP = m_player.maxHP = 100;
	m_player.currentShield = m_player.maxShield = 50;
	m_player.speed = 5.0f;													//플레이어 이동속도
	m_player.frameCount = 0;
	m_player.frameX = 0;
	m_player.frameY = 0;
	m_player.isLeft = false;												//플레이어 왼쪽보는가?
	m_player.animation = IDLE;

	m_player.gunDelay = 0;			//총딜레이

	m_player.nowCharacter = JIMMY;
	m_player.life = true;
	m_player.dash = false;
	m_player.melee = false;
	m_player.hit = false;
	m_player.img->setFrameY(4);		//4번은 IDLE 애니메이션임

	return S_OK;
}

void jimmy::release()
{
}

void jimmy::update()
{
	m_player.enemy_hitRc = RectMakeCenter(m_player.x, m_player.y, 34, 56);		//적에게 피격당하는 렉트 생성	x,y기준으로 생성
	m_player.wall_hitRc = RectMakeCenter(m_player.x, m_player.y + 22, 34, 21);	//벽에 부딪히는 렉트 생성

	move();			//이동명령에 관한 함수
	command();		//커맨드 (부모클래스에있음 더블연타시 대쉬를 출력함)

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)&&!m_player.dash)	//대쉬중이 아니고 클릭시 파이어
	{
		fire();
	}
	melee();	//근접공격 (앵글오류로 보류)

	hit();		//피격 숫자1번

	dead();		//사망 2번

	animation();	//애니메이션 함수

	

}
void jimmy::render()
{

	m_player.img->frameRender(getMemDC(), m_player.enemy_hitRc.left-40, m_player.enemy_hitRc.top - 30);

	HBRUSH MyBrush, OldBrush;
	HPEN MyPen, OldPen;

	MyBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 255));		// 투명한 렉트생성
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

	TextOut(getMemDC(), m_player.x, m_player.y - 100, _str, lstrlen(_str));		//텍스트 출력용
	TCHAR str[128];
	switch (m_player.nowCharacter)		//nowCharcher 는 현재캐릭터를 알려줌
	{
	case JIMMY:
		wsprintf(str, TEXT("현재 캐릭터 : 지미"));
		break;
	case RIDER:
		wsprintf(str, TEXT("현재 캐릭터 : 라이더"));
		break;
	}
	sprintf(str, TEXT("%f"), m_player.angle);
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, str, lstrlen(str));

	LineMake(getMemDC(),m_player.x, m_player.y, m_player.x + cosf(m_player.angle) * 100, m_player.y + (-sinf(m_player.angle) * 100));
}

void jimmy::animation()
{
	//현재 플레이에의 애니메이션 enum문값에 따라 애니메이션을출력함

	//플레이어 대쉬 애니메이션
	if (m_player.animation == DASH)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 1) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 9 : m_player.frameY = 0;
	}

	//플레이어 사망 애니메이션
	if (m_player.animation == DEATH)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 10) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 10 : m_player.frameY = 1;
	}

	//플레이어 땅파기 애니메이션
	if (m_player.animation == DIG)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 2) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 11 : m_player.frameY = 2;
	}

	//플레이어 피격 애니메이션
	if (m_player.animation == HIT)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 1) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 12 : m_player.frameY = 3;
	}

	//플레이어 기본 애니메이션
	if (m_player.animation == IDLE)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 11) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 13 : m_player.frameY = 4;
	}

	//플레이어 근접공격 애니메이션
	if (m_player.animation == MELEE)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 6) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 14 : m_player.frameY = 5;
	}

	//플레이어 달리기 애니메이션
	if (m_player.animation == RUN)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 6 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 5) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 15 : m_player.frameY = 6;
	}
	//플레이어 텔리포트 애니메이션
	if (m_player.animation == TELEPORT)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 7) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 16 : m_player.frameY = 7;
	}

	//플레이어 걷기 애니메이션
	if (m_player.animation == WALK)
	{
		m_player.frameCount++;
		if (m_player.frameCount % 5 == 0)
		{
			m_player.frameCount = 0;
			m_player.frameX++;
			if (m_player.frameX > 5) m_player.frameX = 0;
		}
		m_player.isLeft ? m_player.frameY = 17 : m_player.frameY = 8;
	}

	m_player.img->setFrameX(m_player.frameX);		//프레임값을 바꿔줌 X
	m_player.img->setFrameY(m_player.frameY);		//프레임값을 바꿔줌 Y

}

void jimmy::move()
{
	//마우스보다 커지거나 작아지면 좌우 값을 바꿈
	if (ptMouse.x < m_player.x)m_player.isLeft = true;
	else m_player.isLeft = false;


	if (KEYMANAGER->isStayKeyDown('A')&&!m_player.melee)
	{
		m_player.x -= m_player.speed;
		if(!m_player.dash && !m_player.hit) m_player.animation = WALK;

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
	//아무것도 눌리지 않았을때 기본 애니메이션으로 변경
}

void jimmy::melee()
{
	float endX = (float)ptMouse.x;
	float endY = (float)ptMouse.y;

	if (KEYMANAGER->isOnceKeyDown('V')&&!m_player.melee)		
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

void jimmy::hit()
{
	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		m_player.hit = true;
		m_player.frameX = 0;
		m_player.animation = HIT;
	}
	if (m_player.hit)
	{
		number++;
		if (number % 17 == 0) m_player.hit = false;
	}
}

void jimmy::dead()
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

void jimmy::fire()
{
}
