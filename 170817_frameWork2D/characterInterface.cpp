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
	//Ű�� �ԷµǸ� Ŀ�ǵ� ���Ϳ� ��������
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

	if (_vCOMMAND.size() == 0)	//�뽬 ����� �⺻�ִϸ��̼����� ����
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
		wsprintf(_str, TEXT("���ʴ뽬"));
		m_player.x -= m_player.speed+5.0f;
		m_player.animation = DASH;		//�뽬�ִϸ��̼�
	}
	if (_vCOMMAND.size() > 1) if (_vCOMMAND[0] == key_right && _vCOMMAND[1] == key_right)
	{
		m_player.dash = true;
		wsprintf(_str, TEXT("�����ʴ뽬"));
		m_player.x += m_player.speed + 5.0f;
		m_player.animation = DASH;
	}
	if (_vCOMMAND.size() > 1) if (_vCOMMAND[0] == key_up && _vCOMMAND[1] == key_up)
	{

		m_player.dash = true;
		wsprintf(_str, TEXT("���ʴ뽬"));
		m_player.y -= m_player.speed + 5.0f;
		m_player.animation = DASH;
	}
	if (_vCOMMAND.size() > 1) if (_vCOMMAND[0] == key_down && _vCOMMAND[1] == key_down)
	{
		m_player.dash = true;
		wsprintf(_str, TEXT("�Ʒ��ʴ뽬"));
		m_player.y += m_player.speed + 5.0f;
		m_player.animation = DASH;
	}

	if (m_player.dash && once)	//�뽬�� ���������� ������X �� 0���� �ѹ��� �ٲ���  
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

