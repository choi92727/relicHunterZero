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
	bulletInterface *p;
	for (m_viBulletList = m_vBulletList.begin(); m_viBulletList != m_vBulletList.end(); ++m_viBulletList)
	{
		p = *m_viBulletList;
		if (p != NULL)
		{
			delete p;
			p = nullptr;
		}
	}
	m_vBulletList.clear();
}

void bulletManager::update()
{
	bulletMove();
	wallCollsionCheck();
	enemyCollisionCheck();
	objectCollisionCheck();
	CharCollisionCheck();
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


	char text[64];
	wsprintf(text, "bulletSize %d", m_vBulletList.size());

	TextOut(getMemDC(), WINSIZEX / 2, 130, text, strlen(text));
}

void bulletManager::addBullet(GUNTYPE _gunType, int x, int y, float angle, float speed, CHARACTER playerType)
{
	bulletInterface* temp;
	switch (_gunType)
	{
	case GUN_DEFAULT:
		temp = new defaultBullet;
		break;
	case GUN_MACHINE:
		temp = new machineBullet;
		break;
	case GUN_SHOTGUN:
		temp = new shotBullet;
		break;
	case GUN_PLASMA:
		temp = new plasmarBullet;
		break;
	default:
		break;
	}
	temp->init();
	temp->fire(x, y, angle, speed, playerType);
	
	m_vBulletList.push_back(temp);
}

void bulletManager::addCollisionBullet(CHARACTER _char, RECT rc, float damage, float angle, float speed, float range)
{
	bulletInterface* temp = new collisionBullet;
	temp->init(_char, rc, damage, angle, speed, range);

	m_vBulletList.push_back(temp);
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

void bulletManager::enemyCollisionCheck()
{
	vector<enemy*> m_vEnemy = m_enemyManager->getVEnemy();
	vector<enemy*>::iterator m_viEnemy = m_vEnemy.begin();
	for (m_viEnemy; m_viEnemy != m_vEnemy.end(); m_viEnemy++)
	{
		for (m_viBulletList = m_vBulletList.begin(); m_viBulletList != m_vBulletList.end();)
		{
			if ((*m_viBulletList)->getPlayerType() == CHAR_PLAYER) {
				RECT temp;
				if (IntersectRect(&temp, &(*m_viEnemy)->getRect(), &(*m_viBulletList)->getRect()))
				{
					(*m_viEnemy)->setHP((*m_viBulletList)->getDamage());
					deleteBullet(m_viBulletList);
				}
				else
				{
					m_viBulletList++;
				}
			}
			else
			{
				m_viBulletList++;
			}
		}
	}
}

void bulletManager::objectCollisionCheck()
{
	vector<object*> m_vObj = m_objectManager->getVObject();
	vector<object*>::iterator m_viObj = m_vObj.begin();
	for (m_viObj; m_viObj != m_vObj.end(); m_viObj++)
	{
		if (!(*m_viObj)->getIsTeleport()) {
			for (m_viBulletList = m_vBulletList.begin(); m_viBulletList != m_vBulletList.end();)
			{
				RECT temp;
				if (IntersectRect(&temp, &(*m_viObj)->getRect(), &(*m_viBulletList)->getRect()))
				{
					(*m_viObj)->setHP((*m_viBulletList)->getDamage());
					deleteBullet(m_viBulletList);
				}
				else
				{
					m_viBulletList++;
				}
			}
		}
	}
}

void bulletManager::CharCollisionCheck()
{
	for (m_viBulletList = m_vBulletList.begin(); m_viBulletList != m_vBulletList.end();)
	{
		if ((*m_viBulletList)->getPlayerType() == CHAR_ENEMY) {
			RECT temp;
			if (IntersectRect(&temp, &m_character->getEnemy_hitRc(), &(*m_viBulletList)->getRect()))
			{
				//m_character->setCurrentHP(m_character->getCurrentHP() - (*m_viBulletList)->getDamage());
				//deleteBullet(m_viBulletList);
				m_character->damageBullet((*m_viBulletList)->getDamage());
				deleteBullet(m_viBulletList);
			}
			else
			{
				m_viBulletList++;
			}
		}
		else
		{
			m_viBulletList++;
		}
	}
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
	bulletInterface *p;
	(*m_bullet)->release();
	p = *m_bullet;
	delete p;
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



