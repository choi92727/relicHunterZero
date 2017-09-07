#include "stdafx.h"
#include "characterInterface.h"


characterInterface::characterInterface()
{
}


characterInterface::~characterInterface()
{
}

HRESULT characterInterface::init(POINT position)
{
	return S_OK;
}

void characterInterface::release()
{
}

void characterInterface::update()
{
}

void characterInterface::render()
{
}

void characterInterface::animation()
{
}

void characterInterface::move()
{
}

void characterInterface::command()
{
	//키가 입력되면 커맨드 벡터에 값을넣음
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_vCOMMAND.push_back(key_left);
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_vCOMMAND.push_back(key_right);
	}
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		_vCOMMAND.push_back(key_up);
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		_vCOMMAND.push_back(key_down);
	}



	if (_vCOMMAND.size() > 0) _fCommandTime += 0.1f;

	if (_fCommandTime > _fCommandClear)
	{
		_fCommandTime = 0;
		_vCOMMAND.clear();
	}

	if (_vCOMMAND.size() == 0)	//대쉬 종료시 기본애니메이션으로 변경
	{
		once = true;
		m_player.dash = false;
		wsprintf(_str, TEXT(""));
		if (!m_player.hit&&!m_player.melee&&m_player.animation != WALK)
		{
			m_player.animation = IDLE;
		}
	}

	if (_vCOMMAND.size() > 1) if (_vCOMMAND[0] == key_left && _vCOMMAND[1] == key_left)
	{
		m_player.dash = true;
		wsprintf(_str, TEXT("왼쪽대쉬"));
		m_player.x -= m_player.speed+5.0f;
		m_player.animation = DASH;		//대쉬애니메이션
	}
	if (_vCOMMAND.size() > 1) if (_vCOMMAND[0] == key_right && _vCOMMAND[1] == key_right)
	{
		m_player.dash = true;
		wsprintf(_str, TEXT("오른쪽대쉬"));
		m_player.x += m_player.speed + 5.0f;
		m_player.animation = DASH;
	}
	if (_vCOMMAND.size() > 1) if (_vCOMMAND[0] == key_up && _vCOMMAND[1] == key_up)
	{

		m_player.dash = true;
		wsprintf(_str, TEXT("위쪽대쉬"));
		m_player.y -= m_player.speed + 5.0f;
		m_player.animation = DASH;
	}
	if (_vCOMMAND.size() > 1) if (_vCOMMAND[0] == key_down && _vCOMMAND[1] == key_down)
	{
		m_player.dash = true;
		wsprintf(_str, TEXT("아래쪽대쉬"));
		m_player.y += m_player.speed + 5.0f;
		m_player.animation = DASH;
	}

	if (m_player.dash && once)	//대쉬가 실행됬을때 프레임X 를 0으로 한번만 바꿔줌  
	{
		once = false;
		m_player.frameX = 0;
	}
}

void characterInterface::melee()
{
}

void characterInterface::hit()
{
}

void characterInterface::dead()
{
}

void characterInterface::fire()
{
}

