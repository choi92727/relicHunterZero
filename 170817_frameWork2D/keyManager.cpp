#include "stdafx.h"
#include "keyManager.h"


keyManager::keyManager()
{
}


keyManager::~keyManager()
{
}

HRESULT keyManager::init()
{
	for (int i = 0; i < KEY_MAX; i++)
	{
		m_keyUp.set(i, false);
		m_keyDown.set(i, false);
	}
	return S_OK;
}

void keyManager::release()
{
}

bool keyManager::isOnceKeyDown(int num)
{
	if (GetAsyncKeyState(num) & 0x8000)
	{
		if (!m_keyDown[num])
		{
			m_keyDown.set(num, true);
			return true;
		}
	}
	else
	{
		m_keyDown.set(num, false);
	}
	return false;
}

bool keyManager::isOnceKeyUp(int num)
{
	if (GetAsyncKeyState(num) & 0x8000)
	{
		m_keyUp.set(num, true);
	}
	else
	{
		if (m_keyUp[num])
		{
			m_keyUp.set(num, false);
			return true;
		}
	}
	return false;
}

bool keyManager::isStayKeyDown(int num)
{
	if (GetAsyncKeyState(num) & 0x8000) return true;
	return false;
}

bool keyManager::isToggleKey(int num)
{
	if (GetKeyState(num) & 0x0001) return true;
	return false;
}
