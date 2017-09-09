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
	m_player.faceImg = IMAGEMANAGER->findImage("지미상태얼굴");		//체력에따른 지미얼굴
	m_player.x = position.x;
	m_player.y = position.y;
	m_player.enemy_hitRc = RectMakeCenter(m_player.x, m_player.y, 34, 56);	//적에게 피격가능한 렉트
	m_player.wall_hitRc = RectMakeCenter(m_player.x, m_player.y+22, 34, 21);	//벽에 부딪치는 렉트
	m_player.currentHP = m_player.maxHP = 150;
	m_player.currentShield = m_player.maxShield = 50;
	m_player.currentStamina = m_player.maxStamina = 100;	//
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
	m_player.run = false;	// 달리기상태확인

	m_player.meleeAtk = false;		//근접공격 렉트생성확인
	m_player.meleeAtkOnce = false;	//렉트생성 한번만실행
	m_player.die = false;		//캐릭터 죽음 애니메이션 후에 진짜죽게만드는값

	m_player.img->setFrameY(4);		//4번은 IDLE 애니메이션임


	//체력바
	hpBar = new characterProgressBar;
	hpBar->init("체력바앞", "체력바뒤", 98, 42, 172, 52);

	shieldBar = new characterProgressBar;
	shieldBar->init("쉴드바앞", "쉴드바뒤", 92, 72, 158, 29);

	staminaBar = new characterProgressBar;
	staminaBar->init("스테미너바앞", "스테미너바뒤", 95, 101, 153, 6);

	hpNumDraw = new numberDrawManager;
	hpNumDraw->init("별숫자", 3);

	shieldNumDraw = new numberDrawManager;
	shieldNumDraw->init("별숫자", 2);
	return S_OK;
}

void jimmy::release()
{
	SAFE_DELETE(hpBar);
	SAFE_DELETE(shieldBar);
	SAFE_DELETE(staminaBar);
	SAFE_DELETE(hpNumDraw);
	SAFE_DELETE(shieldNumDraw);
}

void jimmy::update(POINT pt)
{
	//프로그래스바
	hpBar->setGauge(m_player.currentHP, m_player.maxHP);
	hpBar->update();

	hpNumDraw->update(m_player.currentHP);
	shieldNumDraw->update(m_player.currentShield);


	shieldBar->setGauge(m_player.currentShield, m_player.maxShield);
	shieldBar->update();

	staminaBar->setGauge(m_player.currentStamina,m_player.maxStamina);
	staminaBar->update();
	
	hpFaceInfo();

	move();			//이동명령에 관한 함수

	m_player.enemy_hitRc = RectMakeCenter(m_player.x, m_player.y, 34, 56);		//적에게 피격당하는 렉트 생성	x,y기준으로 생성
	m_player.wall_hitRc = RectMakeCenter(m_player.x, m_player.y + 22, 34, 21);	//벽에 부딪히는 렉트 생성




	command();		//커맨드 (부모클래스에있음 더블연타시 대쉬를 출력함)

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)&&!m_player.dash)	//대쉬중이 아니고 클릭시 파이어
	{
		m_player.currentHP -= 1;		//테스트용
		m_player.currentShield -= 1;	//테스트용
		fire();
	}
	melee(pt);	//근접공격 
	
	run();		//달리기

	hit();		//피격 숫자1번

	dead();		//사망 2번


	animation();	//애니메이션 함수



}
void jimmy::render(POINT pt)
{
	//프로그래스 바
	hpBar->render();
	shieldBar->render();
	staminaBar->render();
	hpNumDraw->render(200,45,1);
	shieldNumDraw->render(210,75,1);
	m_player.faceImg->frameRender(getMemDC(), 1, 16);


	m_player.img->frameRender(getMemDC(), m_player.enemy_hitRc.left-40 - pt.x, m_player.enemy_hitRc.top - 30 - pt.y);

	HBRUSH MyBrush, OldBrush;
	HPEN MyPen, OldPen;

	MyBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 255));		// 투명한 렉트생성
	OldBrush = (HBRUSH)SelectObject(getMemDC(), MyBrush);
	MyPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	OldPen = (HPEN)SelectObject(getMemDC(), MyPen);

	/*Rectangle(getMemDC(), m_player.enemy_hitRc.left -pt.x, m_player.enemy_hitRc.top-pt.y,
		m_player.enemy_hitRc.right - pt.x, m_player.enemy_hitRc.bottom - pt.y);*/
	Rectangle(getMemDC(), m_player.wall_hitRc.left-pt.x, m_player.wall_hitRc.top-pt.y,
		m_player.wall_hitRc.right-pt.x, m_player.wall_hitRc.bottom-pt.y);

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

	sprintf(str, TEXT("x : %f, y : %f"), m_player.x, m_player.y);
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2 + 40, str, lstrlen(str));
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
		if (m_player.frameX ==10)		//     죽었을때 마지막프레임에 도달시 진짜죽음실행
		{
			m_player.die = true;
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


	if (m_player.die)	//사망처리
	{
		m_player.frameX = 9;

		m_player.isLeft ? m_player.frameY = 10 : m_player.frameY = 1;
		Sleep(1000);
		PostQuitMessage(0);	//사망
	}

	m_player.img->setFrameX(m_player.frameX);		//프레임값을 바꿔줌 X
	m_player.img->setFrameY(m_player.frameY);		//프레임값을 바꿔줌 Y

}

void jimmy::move()
{
	//마우스보다 커지거나 작아지면 좌우 값을 바꿈
	if (ptMouse.x < WINSIZEX/2)m_player.isLeft = true;
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

void jimmy::melee(POINT pt)
{

	if (KEYMANAGER->isOnceKeyDown('V')&&!m_player.melee)		
	{
		m_player.angle = getAngle(m_player.x, m_player.y, pt.x + ptMouse.x, pt.y + ptMouse.y);
		m_player.melee = true;
		m_player.frameX = 0;
		m_player.meleeAtkOnce = true;
	}

	if (m_player.melee)
	{
		if (count >20)
		{
			m_player.x += cosf(m_player.angle) * m_player.speed;
			m_player.y += -sinf(m_player.angle) * m_player.speed;
			
			if (m_player.meleeAtkOnce == true)
			{
				m_player.meleeAtk = true;
				m_player.meleeAtkOnce = false;
			}
		}
		m_player.animation = MELEE;
		count++;
		if (count % 35 == 0)
		{
			m_player.melee = false;

			m_player.meleeAtk = false;
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

void jimmy::hpFaceInfo()
{
	if ((m_player.maxHP / 3) * 2 < m_player.currentHP)
	{
		m_player.faceImg->setFrameX(0);
	}
	else if (m_player.maxHP / 3 < m_player.currentHP)
	{
		m_player.faceImg->setFrameX(1);
	}
	else if (m_player.maxHP /3 > m_player.currentHP)
	{
		m_player.faceImg->setFrameX(2);
	}
}

void jimmy::run()
{
	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT)&&!m_player.melee&&!m_player.dash)
	{
		if (m_player.currentStamina > 0)	//스테미너가 0보다 많을경우 달리기실행
		{
			m_player.run = true;
		}
		else          //아니면 달리기 종료
		{
			m_player.run = false;
			m_player.speed = 5.0f;	//고정값으로 해줌
		}

		if (m_player.run)
		{
			m_player.animation = RUN;
			m_player.speed = 7.5f;	//이동속도 50%증가
			runDelay++;
			if (runDelay % 2 == 0)
			{
				m_player.currentStamina--;	//달릴때 스테미너감소
			}
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LSHIFT))	//쉬프트키를 떼면 달리기종료
	{
		m_player.run = false;
		m_player.speed = 5.0f;
	}
	if (m_player.currentStamina < 100 && !m_player.run)	//스테미너가 100보다 작고 달리는중이 아니라면
	{
		runDelay++;
		if (runDelay%3==0)
		{
			m_player.currentStamina++;	//스테미너 회복
		}
	}
}
