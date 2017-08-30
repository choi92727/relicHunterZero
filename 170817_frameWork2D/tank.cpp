#include "stdafx.h"
#include "tank.h"


tank::tank()
{
}


tank::~tank()
{
}

HRESULT tank::init()
{
	m_direction = TANKDIRECTION_RIGHT;
	m_image = IMAGEMANAGER->addFrameImage("tank", "images/tank.bmp", 128, 32, 4, 1, true, RGB(255, 0, 255));
	m_speed = 100.0f;
	return S_OK;
}

void tank::release()
{
}

void tank::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		m_direction = TANKDIRECTION_LEFT;
		tankMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		m_direction = TANKDIRECTION_RIGHT;
		tankMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		m_direction = TANKDIRECTION_UP;
		tankMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		m_direction = TANKDIRECTION_DOWN;
		tankMove();
	}
	m_rc = RectMakeCenter(m_x, m_y, m_image->getFrameWidth(), m_image->getFrameHeight());
}

void tank::render()
{
	m_image->frameRender(getMemDC(), m_rc.left, m_rc.top);
}

void tank::tankMove()
{

	float elapsedTime = TIMEMANAGER->getElasedTime();
	float moveSpeed = elapsedTime*m_speed;

	switch (m_direction)
	{
	case TANKDIRECTION_LEFT:
		m_image->setFrameX(3);
		m_x -= moveSpeed;
		break;
	case TANKDIRECTION_RIGHT:
		m_image->setFrameX(1);
		m_x += moveSpeed;
		break;
	case TANKDIRECTION_UP:
		m_image->setFrameX(0);
		m_y -= moveSpeed;
		break;
	case TANKDIRECTION_DOWN:
		m_image->setFrameX(2);
		m_y += moveSpeed;
		break;
	}

	if (!findUnmoveTile())
	{
		switch (m_direction)
		{
		case TANKDIRECTION_LEFT:
			m_image->setFrameX(3);
			m_x += moveSpeed;
			break;
		case TANKDIRECTION_RIGHT:
			m_image->setFrameX(1);
			m_x -= moveSpeed;
			break;
		case TANKDIRECTION_UP:
			m_image->setFrameX(0);
			m_y += moveSpeed;
			break;
		case TANKDIRECTION_DOWN:
			m_image->setFrameX(2);
			m_y -= moveSpeed;
			break;
		}
	}
}

void tank::setTankPosition()
{
	m_rc = m_tankMap->getTile()[m_tankMap->getPosFirst()].rc;
	m_x = m_rc.left + (m_rc.right - m_rc.left) / 2;
	m_y = m_rc.top + (m_rc.bottom - m_rc.top) / 2;

}

bool tank::findUnmoveTile()
{
	POINT pt1, pt2;
	switch (m_direction)
	{
	case TANKDIRECTION_LEFT:
		for (int i = 0; i < TILEX*TILEY; i++)
		{
			pt1 = { m_rc.left,m_rc.top+1 };
			pt2 = { m_rc.left,m_rc.bottom-1 };
			if (PtInRect(&m_tankMap->getTile()[i].rc, pt1))
			{
				if (m_tankMap->getAttribute()[i] == ATTR_UNMOVE)
				{
					m_rc = m_tankMap->getTile()[i].rc;
					m_x = m_rc.left + (m_rc.right - m_rc.left) / 2;
					m_y = m_rc.top + (m_rc.bottom - m_rc.top) / 2;
					return false;
				}
			}
			if (PtInRect(&m_tankMap->getTile()[i].rc, pt2))
			{
				if (m_tankMap->getAttribute()[i] == ATTR_UNMOVE)
				{
					m_rc = m_tankMap->getTile()[i].rc;
					m_x = m_rc.left + (m_rc.right - m_rc.left) / 2;
					m_y = m_rc.top + (m_rc.bottom - m_rc.top) / 2;
					return false;
				}
			}
		}
		break;
	case TANKDIRECTION_RIGHT:
		for (int i = 0; i < TILEX*TILEY; i++)
		{
			pt1 = { m_rc.right,m_rc.top+1 };
			pt2 = { m_rc.right,m_rc.bottom-1 };
			if (PtInRect(&m_tankMap->getTile()[i].rc, pt1))
			{
				if (m_tankMap->getAttribute()[i] == ATTR_UNMOVE)
				{

					return false;
				}
			}
			if (PtInRect(&m_tankMap->getTile()[i].rc, pt2))
			{
				if (m_tankMap->getAttribute()[i] == ATTR_UNMOVE)
				{
					return false;
				}
			}
		}
		break;
	case TANKDIRECTION_UP:
		for (int i = 0; i < TILEX*TILEY; i++)
		{
			pt1 = { m_rc.right-1,m_rc.top };
			pt2 = { m_rc.left+1,m_rc.top };
			if (PtInRect(&m_tankMap->getTile()[i].rc, pt1))
			{
				if (m_tankMap->getAttribute()[i] == ATTR_UNMOVE)
				{
					return false;
				}
			}
			if (PtInRect(&m_tankMap->getTile()[i].rc, pt2))
			{
				if (m_tankMap->getAttribute()[i] == ATTR_UNMOVE)
				{
					return false;
				}
			}
		}
		break;
	case TANKDIRECTION_DOWN:
		for (int i = 0; i < TILEX*TILEY; i++)
		{
			pt1 = { m_rc.right-1,m_rc.bottom };
			pt2 = { m_rc.left+1,m_rc.bottom };
			if (PtInRect(&m_tankMap->getTile()[i].rc, pt1))
			{
				if (m_tankMap->getAttribute()[i] == ATTR_UNMOVE)
				{
					return false;
				}
			}
			if (PtInRect(&m_tankMap->getTile()[i].rc, pt2))
			{
				if (m_tankMap->getAttribute()[i] == ATTR_UNMOVE)
				{
					return false;
				}
			}
		}
		break;
	}
	return true;
}
