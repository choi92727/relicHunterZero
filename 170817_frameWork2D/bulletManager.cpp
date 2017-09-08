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
	bulletMove();
	wallCollsionCheck();
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

void bulletManager::bulletMove()
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
 
void bulletManager::wallCollsionCheck()
{
	for (m_viBulletList = m_vBulletList.begin(); m_viBulletList != m_vBulletList.end();)
	{
		int x = (*m_viBulletList)->getX() / TILESIZE;
		int y = (*m_viBulletList)->getY() / TILESIZE;

		if (m_tagTile[y][x].attribute == ATTR_UNMOVE)
		{
			deleteBullet(m_viBulletList);
		}
		else
		{
			m_viBulletList++;
		}
	}
}


void bulletManager::deleteBullet(viBulletList &m_bullet)
{
	(*m_bullet)->release();
	m_bullet = m_vBulletList.erase(m_bullet);
}

void bulletManager::loadTile(char* mapName)
{
	HANDLE file;
	DWORD read;
	file = CreateFile(mapName,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	//타일 불러오기
	ReadFile(file, m_tagTile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	//에너미 불러오기
	CloseHandle(file);
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			if (m_tagTile[y][x].terrainFrameY == 0 || (m_tagTile[y][x].terrainFrameX >= 15 && m_tagTile[y][x].terrainFrameX <= 18) || (m_tagTile[y][x].terrainFrameX >= 25 && m_tagTile[y][x].terrainFrameX <= 32) || m_tagTile[y][x].terrainFrameX >= 39)
			{
				m_tagTile[y][x].terrain = TR_WALL;
			}
			if (m_tagTile[y][x].terrain == TR_WALL) m_tagTile[y][x].attribute = ATTR_UNMOVE;
		}
	}
}

