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
	for (m_viBulletList = m_vBulletList.begin(); m_viBulletList != m_vBulletList.end();)
	{
		(*m_viBulletList)->update();
		if ((*m_viBulletList)->getRange() < 0)
		{
			deleteBullet(m_viBulletList);
		}
		else
		{
			m_viBulletList++;
		}
	}
}

void bulletManager::render()
{
	for (m_viBulletList = m_vBulletList.begin(); m_viBulletList != m_vBulletList.end(); m_viBulletList++)
	{
		(*m_viBulletList)->render();
	}
	//char text[64];
	//wsprintf(text, "bulletSize %d",m_vBulletList.size());

	//TextOut(getMemDC(), 10, 130, text, strlen(text));
}

void bulletManager::render(POINT pt)
{
	for (m_viBulletList = m_vBulletList.begin(); m_viBulletList != m_vBulletList.end(); m_viBulletList++)
	{
		(*m_viBulletList)->render(pt);
	}
	//char text[64];
	//wsprintf(text, "bulletSize %d",m_vBulletList.size());

	//TextOut(getMemDC(), 10, 130, text, strlen(text));
}

void bulletManager::addBullet(bulletInterface &m_bullet)
{
	m_vBulletList.push_back(&m_bullet);
}

bool bulletManager::enemyCollisionCheck(RECT & _rc)
{
	//for (m_viBulletList = m_vBulletList.begin(); m_viBulletList != m_vBulletList.end();)
	//{
	//	if ((*m_viBulletList)->getPlayerType() == CHAR_ENEMY)
	//	{
	//		m_viBulletList++;
	//		continue;
	//	}

	//	if ()
	//	{
	//		deleteBullet(m_viBulletList);
	//	}
	//	else
	//	{
	//		m_viBulletList++;
	//	}
	//}
	return false;
}



void bulletManager::deleteBullet(viBulletList &m_bullet)
{
	(*m_bullet)->release();
	m_bullet = m_vBulletList.erase(m_bullet);
}

