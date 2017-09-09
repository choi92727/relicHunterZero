#include "stdafx.h"
#include "collisionBullet.h"


collisionBullet::collisionBullet()
{
}


collisionBullet::~collisionBullet()
{
}

HRESULT collisionBullet::init(CHARACTER _char, RECT rc, float damage)
{
	m_playerType = _char;
	m_rc = rc;
	m_damage = damage;

	return S_OK;
}

void collisionBullet::release()
{
}

void collisionBullet::update()
{
}

void collisionBullet::render()
{
	Rectangle(getMemDC(), m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
}

void collisionBullet::render(POINT pt)
{
}

void collisionBullet::setRect(RECT rc)
{
	m_rc = rc;
}



