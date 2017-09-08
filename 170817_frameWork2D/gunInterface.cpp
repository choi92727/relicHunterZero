#include "stdafx.h"
#include "gunInterface.h"


gunInterface::gunInterface()
{
}


gunInterface::~gunInterface()
{
}

HRESULT gunInterface::init(CHARACTER playerType)
{
	return E_NOTIMPL;
}

void gunInterface::release()
{
}

void gunInterface::update()
{
}

void gunInterface::render()
{
}

void gunInterface::render(POINT pt)
{
}

void gunInterface::fire()
{
}

void gunInterface::setAngle()
{
}

void gunInterface::setPosition(int x, int y)
{
}

void gunInterface::reload()
{
	if (m_maxBullet > m_currentBullet)
	{
		if (m_totalBullet <= m_maxBullet)
		{
			m_currentBullet += m_totalBullet;
			m_totalBullet = 0;
		}
		else
		{
			m_totalBullet -= (m_maxBullet - m_currentBullet);
			m_currentBullet += (m_maxBullet - m_currentBullet);
			
		}
	}
}
