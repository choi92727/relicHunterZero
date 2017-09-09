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

	_fCommandClear = 2.5f;	//커맨드입력시간
	_fCommandTime = 0.0f;

	ZeroMemory(&m_player, sizeof(m_player));

	m_player.img = IMAGEMANAGER->findImage("라이더");		//라이더 이미지를넣음
	m_player.faceImg = IMAGEMANAGER->findImage("라이더상태얼굴");		//체력에따른 라이더얼굴
	m_player.shieldRender = false;

	m_player.x = position.x;
	m_player.y = position.y;
	m_player.enemy_hitRc = RectMakeCenter(m_player.x, m_player.y, 34, 72);	//적에게 피격가능한 렉트
	m_player.wall_hitRc = RectMakeCenter(m_player.x, m_player.y + 32, 56, 22);	//벽에 부딪치는 렉트
	m_player.currentHP = m_player.maxHP = 150;
	m_player.currentShield = m_player.maxShield = 50;

	m_player.shieldGenDealy = 2.0f;
	m_player.shieldGenTime = 0;
	m_player.shieldGen = false;

	m_player.currentStamina = m_player.maxStamina = 100;	//
	m_player.speed = 5.0f;													//플레이어 이동속도
	m_player.frameCount = 0;
	m_player.frameX = 0;
	m_player.frameY = 0;
	m_player.isLeft = false;												//플레이어 왼쪽보는가?
	m_player.animation = IDLE;

	m_player.gunDelay = 0;			//총딜레이

	m_player.nowCharacter = RIDER;

	m_player.life = true;
	m_player.dash = false;
	m_player.melee = false;
	m_player.hit = false;
	m_player.run = false;				//
	m_player.runStartDelay = false;		//

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
	//프로그래스바
	hpBar->setGauge(m_player.currentHP, m_player.maxHP);
	hpBar->update();

	hpNumDraw->update(m_player.currentHP);
	shieldNumDraw->update(m_player.currentShield);


	shieldBar->setGauge(m_player.currentShield, m_player.maxShield);
	shieldBar->update();

	staminaBar->setGauge(m_player.currentStamina, m_player.maxStamina);
	staminaBar->update();

	hpFaceInfo();


	m_player.enemy_hitRc = RectMakeCenter(m_player.x, m_player.y, 34, 72);			//적에게 피격당하는 렉트생성 x,y기준으로 생성
	m_player.wall_hitRc = RectMakeCenter(m_player.x, m_player.y + 32, 56, 22);		//벽에 부딪히는 렉트생성


	move();			//이동명령에 관한 함수

	command();		//커맨드 (부모클래스에있음 더블연타시 대쉬를 출력함)

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && !m_player.dash)	//대쉬중이 아니고 클릭시 파이어
	{
		fire();
	}
	melee(pt);	//근접공격

	run();		//달리기

	hit();		//피격

	damage();

	dead();		//사망

	animation();	//애니메이션 함수

	shieldRegen();
}

void rider::render(POINT pt)
{
	//프로그래스 바
	hpBar->render();
	shieldBar->render();
	staminaBar->render();
	hpNumDraw->render(200, 45, 1);
	shieldNumDraw->render(210, 75, 1);
	m_player.faceImg->frameRender(getMemDC(), 1, 16);


	m_player.img->frameRender(getMemDC(), m_player.enemy_hitRc.left - 38 - pt.x, m_player.enemy_hitRc.top - 30 - pt.y);

	if (m_player.shieldRender)
	{
		m_player.shieldImg->alphaRender(getMemDC(), m_player.enemy_hitRc.left - 40 + 28 + 8 - pt.x, m_player.enemy_hitRc.top - 30 + 35 - pt.y, 100);
	}
	HBRUSH MyBrush, OldBrush;
	HPEN MyPen, OldPen;

	MyBrush = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 255));		//투명한 렉트생성
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

	LineMake(getMemDC(), m_player.x, m_player.y, m_player.x + cosf(m_player.angle) * 100, m_player.y + (-sinf(m_player.angle) * 100));

	sprintf(str, TEXT("x : %f, y : %f"), m_player.x, m_player.y);
	TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2 + 40, str, lstrlen(str));
}

void rider::animation()
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
		m_player.isLeft ? m_player.frameY = 8 : m_player.frameY = 0;

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
		if (m_player.frameX == 10)	//     죽었을때 마지막프레임에 도달시 진짜죽음실행
		{
			m_player.die = true;
		}
		m_player.isLeft ? m_player.frameY = 9 : m_player.frameY = 1;
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
		m_player.isLeft ? m_player.frameY = 10 : m_player.frameY = 2;
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
		m_player.isLeft ? m_player.frameY = 11 : m_player.frameY = 3;
	}

	//플레이어 기본 애니메이션
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
		m_player.isLeft ? m_player.frameY = 13 : m_player.frameY = 5;
	}

	//플레이어 텔리포트 애니메이션
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

	//플레이어 걷기 애니메이션
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

void rider::move()
{
	//마우스보다 커지거나 작아지면 좌우 값을 바꿈
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
	//아무것도 눌리지 않았을때 기본 애니메이션으로 변경
}

void rider::melee(POINT pt)
{

	if (KEYMANAGER->isOnceKeyDown('V') && !m_player.melee)
	{
		m_player.meleeEnd = false;

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
				m_player.melee_atkRc = RectMakeCenter(m_player.x + (cosf(m_player.angle) * 50), m_player.y + (-sinf(m_player.angle) * 50), 60, 60);

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

			m_player.meleeEnd = true;
			count = 0;
		}
	}

}

void rider::hit()
{
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
	if (KEYMANAGER->isStayKeyDown(VK_LSHIFT) && !m_player.melee && !m_player.dash&&
		m_player.animation != IDLE)								//가만히있을때 달리지않음
	{
		if (m_player.currentStamina > 0 && !m_player.runStartDelay)	//스테미너가 0보다 많을경우 달리기실행
		{
			m_player.run = true;
		}
		else          //아니면 달리기 종료
		{
			m_player.runStartDelay = true;
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
		if (m_player.currentStamina <10)
		{
			m_player.runStartDelay = true;
		}
		m_player.run = false;
		m_player.speed = 5.0f;
	}
	if (m_player.currentStamina < 100 && !m_player.run)	//스테미너가 100보다 작고 달리는중이 아니라면
	{
		runDelay++;
		if (runDelay % 3 == 0)
		{
			m_player.currentStamina++;	//스테미너 회복
		}
	}
	if (m_player.currentStamina > 10) m_player.runStartDelay = false;
}

void rider::shieldRegen()
{
	if (m_player.shieldGen)	//쉴드젠이 트루일때 쉴드 젠
	{
		if (m_player.maxShield > m_player.currentShield)
		{
			shieldCount++;
			if (shieldCount % 3 == 0)
			{
				m_player.currentShield++;
			}
		}
	}

	if (m_player.shieldGenTime > m_player.shieldGenDealy)
	{
		m_player.shieldGen = true;
		m_player.shieldGenTime -= 0.02f;
	}
	else
	{
		m_player.shieldGen = false;
	}

	if (m_player.hit)
	{
		m_player.shieldGenTime = 0;
	}
	else
	{
		m_player.shieldGenTime += 0.02f;
	}
}

void rider::damage()
{
	if (m_player.dash)
	{
		bullet_damage = 0;
	}
	if (m_player.damage)
	{
		if (m_player.currentShield >0)
		{
			m_player.currentShield -= bullet_damage;
			m_player.shieldRender = true;
		}
		else
		{
			m_player.currentHP -= bullet_damage;
		}
		m_player.damage = false;
	}

	if (m_player.shieldRender)
	{
		switch (shieldRenderCount)
		{
		case 0:
			m_player.shieldImg = IMAGEMANAGER->findImage("쉴드0");
			break;
		case 1:
			m_player.shieldImg = IMAGEMANAGER->findImage("쉴드1");
			break;
		case 2:
			m_player.shieldImg = IMAGEMANAGER->findImage("쉴드2");
			break;
		case 3:
			m_player.shieldImg = IMAGEMANAGER->findImage("쉴드3");
			break;
		case 4:
			m_player.shieldImg = IMAGEMANAGER->findImage("쉴드4");
			break;
		case 5:
			m_player.shieldImg = IMAGEMANAGER->findImage("쉴드5");
			break;
		}
		//m_player.shieldImg->setFrameX(shieldRenderCount);
		shieldRenderTemp++;
		if (shieldRenderTemp % 5 == 0)
		{
			shieldRenderCount++;

		}
		if (shieldRenderCount > 5)
		{
			m_player.shieldRender = false;
			shieldRenderCount = 0;
		}
	}

}

void rider::damageBullet(float damage)
{
	m_player.hit = true;
	m_player.frameX = 0;
	if (m_player.currentShield <= 0)
	{
		m_player.animation = HIT;
	}

	m_player.damage = true;//데미지판정

	bullet_damage = damage;
}