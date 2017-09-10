#include "stdafx.h"
#include "collisionBullet.h"


collisionBullet::collisionBullet()
{
}


collisionBullet::~collisionBullet()
{
}

HRESULT collisionBullet::init(CHARACTER _char, RECT rc, float damage, float angle, float speed, float range)
{
	m_playerType = _char;
	m_rc = rc;
	m_damage = damage;
	m_angle = angle;
	m_speed = speed;
	m_range = range;

	m_x = (m_rc.left + m_rc.right) / 2;
	m_y = (m_rc.top + m_rc.bottom) / 2;
	return S_OK;
}
void collisionBullet::release()
{
}

void collisionBullet::update()
{
	m_rc.left += cos(m_angle) * m_speed;
	m_rc.right += cos(m_angle) * m_speed;

	m_rc.top += -sin(m_angle) * m_speed;
	m_rc.bottom += -sin(m_angle) * m_speed;

	m_range -= m_speed;

	m_x = (m_rc.left + m_rc.right) / 2;
	m_y = (m_rc.top + m_rc.bottom) / 2;
}

void collisionBullet::render()
{
	//Rectangle(getMemDC(), m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
}

void collisionBullet::render(POINT pt)
{
	Rectangle(getMemDC(), m_rc.left - pt.x, m_rc.top - pt.y, m_rc.right - pt.x, m_rc.bottom - pt.y);
}

void collisionBullet::setRect(RECT rc)
{
	m_rc = rc;
}



