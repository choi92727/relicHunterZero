#include "stdafx.h"
#include "bulletManager.h"


bulletManager::bulletManager()
{
}


bulletManager::~bulletManager()
{
}

HRESULT bulletManager::init()
{
	return S_OK;
}

void bulletManager::release()
{
}

void bulletManager::update()
{
	cnt = 0;
	for (m_viBulletList = m_vBulletList.begin(); m_viBulletList != m_vBulletList.end(); m_viBulletList++)
	{
		cnt += (*m_viBulletList)->getBulletSize();
	}
}

void bulletManager::render()
{
	char text[64];
	wsprintf(text, "bulletSize %d", cnt);

	TextOut(getMemDC(), 10, 130, text, strlen(text));
}

void bulletManager::addBullet(bulletInterface &m_bullet)
{
	m_vBulletList.push_back(&m_bullet);
}

void bulletManager::checkBullet()
{
}
