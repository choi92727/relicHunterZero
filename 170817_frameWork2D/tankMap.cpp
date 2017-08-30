#include "stdafx.h"
#include "tankMap.h"


tankMap::tankMap()
{
}


tankMap::~tankMap()
{
}

HRESULT tankMap::init()
{
	IMAGEMANAGER->addFrameImage("tilemap", "images/tilemap.bmp", 640, 256, SAMPLETILEX, SAMPLETILEY);

	this->load();
	return E_NOTIMPL;
}

void tankMap::release()
{
}

void tankMap::update()
{
}

void tankMap::render()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender("tilemap", getMemDC(), m_tiles[i].rc.left,
			m_tiles[i].rc.top, m_tiles[i].terrainFrameX, m_tiles[i].terrainFrameY);

		if (m_tiles[i].obj == OBJ_NONE) continue;

		IMAGEMANAGER->frameRender("tilemap", getMemDC(), m_tiles[i].rc.left,
			m_tiles[i].rc.top, m_tiles[i].objFrameX, m_tiles[i].objFrameY);
	}
}

void tankMap::load()
{
	HANDLE file;
	DWORD read;
	file = CreateFile("tileMap.map",
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	ReadFile(file, m_tiles, sizeof(tagTile)*TILEX*TILEY, &read, NULL);
	ReadFile(file, m_pos, sizeof(int) * 2, &read, NULL);
	CloseHandle(file);
	for (int i = 0; i < TILEX*TILEY; i++)
	{
		if (m_tiles[i].obj == OBJ_TANK1 || m_tiles[i].obj == OBJ_TANK2)
		{
			m_tiles[i].obj = OBJ_NONE;
		}
	}
	memset(m_attribute, 0, sizeof(DWORD)*TILEX*TILEY);

	for (int i = 0; i < TILEX*TILEY; i++)
	{
		if (m_tiles[i].terrain == TR_WATER)m_attribute[i] = ATTR_UNMOVE;
		if (m_tiles[i].obj == OBJ_BLOCK1)m_attribute[i] = ATTR_UNMOVE;
		if (m_tiles[i].obj == OBJ_BLOCK2)m_attribute[i] = ATTR_UNMOVE;
	}
}
