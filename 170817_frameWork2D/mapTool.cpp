#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	
	SOUNDMANAGER->play("�Ҿƹ�����11��", 0.5f);
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			tile[y][x].rc = RectMake(TILESIZE * x, TILESIZE * y, TILESIZE, TILESIZE);
			tile[y][x].terrain = TR_NONE;
			if (tile[y][x].rc.left > WINSIZEX || tile[y][x].rc.top > WINSIZEY - 196 || tile[y][x].rc.right < 0 || tile[y][x].rc.bottom < 0) tileOn[y][x] = false;
		}
	}

	for (int y = 0; y < SAMPLETILEY; y++)
	{
		for (int x = 0; x < SAMPLETILEX; x++)
		{
			sampleButton[y][x].rcTile = RectMake(TILESIZE * x, WINSIZEY - 192 + y * TILESIZE, TILESIZE, TILESIZE);
			sampleButton[y][x].terrainFrameX = x;
			sampleButton[y][x].terrainFrameY = y;
		}
	}
	currentTileButton = 0;
	buttonUI = RectMake(WINSIZEX - 320, WINSIZEY - 192, 320, 192);
	tileRC = RectMake(WINSIZEX - 160, WINSIZEY - 192, 80, 48);
	exitRC = RectMake(WINSIZEX - 80, WINSIZEY - 192, 80, 48);
	objectRC = RectMake(WINSIZEX - 320, WINSIZEY - 144, 160, 48);
	enemyRC = RectMake(WINSIZEX - 160, WINSIZEY - 144, 160, 48);
	for (int i = 0; i < 2; i++)
	{
		moveRC[i] = RectMake(WINSIZEX - 320 + i * 80, WINSIZEY - 192, 80, 48);
	}
	for (int i = 0; i < 4; i++)
	{
		saveRC[i] = RectMake(WINSIZEX - 320 + i * 80, WINSIZEY - 96, 80, 48);
		loadRC[i] = RectMake(WINSIZEX - 320 + i * 80, WINSIZEY - 48, 80, 48);
	}

	sampleTile = true;
	sampleObject = sampleEnemy = false;

	loookSample = false;
	return S_OK;
}

void mapTool::release()
{
	SOUNDMANAGER->stop("�Ҿƹ�����11��");
}

void mapTool::update()
{
	tileMove();
	tileCheck();
	tileClick();
	saveLoad();
	if (KEYMANAGER->isOnceKeyDown('S'))//���ùڽ� ���̱�
	{
		loookSample = !loookSample;
	}
	if (KEYMANAGER->isOnceKeyDown('L') && sampleTile)//���ùڽ� ���̱�
	{
		moveSample_right();
	}
	if (KEYMANAGER->isOnceKeyDown('K') && sampleTile)//���ùڽ� ���̱�
	{
		moveSample_left();
	}
}

void mapTool::render()
{
	char str[256];
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			if (tileOn[y][x])
			{
				IMAGEMANAGER->frameRender("����", getMemDC(), tile[y][x].rc.left, tile[y][x].rc.top, tile[y][x].terrainFrameX, tile[y][x].terrainFrameY);
				if (tile[y][x].terrain == TR_NONE) sprintf(str, "%d, %d", x, y);
				if (loookSample)
				{
					Rectangle(getMemDC(), tile[y][x].rc.left, tile[y][x].rc.top, tile[y][x].rc.right, tile[y][x].rc.bottom);
					TextOut(getMemDC(), tile[y][x].rc.left + 20, tile[y][x].rc.top + 10, str, strlen(str));
				}
			}
		}
	}

	//������Ʈ
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			if (tile[y][x].obj == OBJ_BOX1) IMAGEMANAGER->frameRender("�ڽ�1", getMemDC(), tile[y][x].rc.left - 42, tile[y][x].rc.top - 40, 0, 0);
			else if (tile[y][x].obj == OBJ_BOX2_1) IMAGEMANAGER->frameRender("�ڽ�2", getMemDC(), tile[y][x].rc.left - 10, tile[y][x].rc.top - 40, 0, 0);
			else if (tile[y][x].obj == OBJ_ROOT1_1) IMAGEMANAGER->frameRender("��Ʈ1", getMemDC(), tile[y][x].rc.left - 32, tile[y][x].rc.top - 38, 0, 0);
			else if (tile[y][x].obj == OBJ_ROOT2_1) IMAGEMANAGER->frameRender("��Ʈ2", getMemDC(), tile[y][x].rc.left - 32, tile[y][x].rc.top - 38, 0, 0);
		}
	}

	//���ʹ�
	for (int i = 0; i < ENEMYMAX; i++)
	{
		if (m_createEnemy[i].enm == ENM_TURTLE)	IMAGEMANAGER->frameRender("�ź���", getMemDC(), m_createEnemy[i].rc.left - 36, m_createEnemy[i].rc.top - 26, 0, 0);
		else if (m_createEnemy[i].enm == ENM_DUCK) IMAGEMANAGER->frameRender("����", getMemDC(), m_createEnemy[i].rc.left - 38, m_createEnemy[i].rc.top - 30, 0, 0);
		else if (m_createEnemy[i].enm == ENM_KAMIKAZE) IMAGEMANAGER->frameRender("���̰���", getMemDC(), m_createEnemy[i].rc.left - 37, m_createEnemy[i].rc.top - 51, 0, 0);
	}

	for (int y = 0; y < SAMPLETILEY; y++)//SAMPLE
	{
		for (int x = 0; x < SAMPLETILEX; x++)
		{
			if (currentTileButton <= x && x < currentTileButton + 15)
			{
				Rectangle(getMemDC(), sampleButton[y][x].rcTile.left, sampleButton[y][x].rcTile.top, sampleButton[y][x].rcTile.right, sampleButton[y][x].rcTile.bottom);
				if (sampleTile) IMAGEMANAGER->frameRender("����", getMemDC(), sampleButton[y][x].rcTile.left, sampleButton[y][x].rcTile.top, sampleButton[y][x].terrainFrameX, sampleButton[y][x].terrainFrameY);
				else if (sampleObject) IMAGEMANAGER->frameRender("������Ʈ", getMemDC(), sampleButton[y][x].rcTile.left, sampleButton[y][x].rcTile.top, sampleButton[y][x].terrainFrameX, sampleButton[y][x].terrainFrameY);
				else if (sampleEnemy) IMAGEMANAGER->frameRender("���ʹ�", getMemDC(), sampleButton[y][x].rcTile.left, sampleButton[y][x].rcTile.top, sampleButton[y][x].terrainFrameX, sampleButton[y][x].terrainFrameY);
			}
		}
	}

	//���콺 Ŀ�� ���õ� ����
	if (sampleTile)	IMAGEMANAGER->frameRender("����", getMemDC(), ptMouse.x - TILESIZE / 2, ptMouse.y - TILESIZE / 2, currentTile.x, currentTile.y);
	else if (sampleObject)
	{
		if (currentTile.x == 0 && currentTile.y == 0) IMAGEMANAGER->frameRender("�ڽ�1", getMemDC(), ptMouse.x - IMAGEMANAGER->findImage("�ڽ�1")->getFrameWidth() / 2, ptMouse.y - IMAGEMANAGER->findImage("�ڽ�1")->getFrameHeight() / 2, 0, 0);
		else if (currentTile.x == 1 && currentTile.y == 0 || currentTile.x == 2 && currentTile.y == 0) IMAGEMANAGER->frameRender("�ڽ�2", getMemDC(), ptMouse.x - IMAGEMANAGER->findImage("�ڽ�2")->getFrameWidth() / 4, ptMouse.y - IMAGEMANAGER->findImage("�ڽ�2")->getFrameHeight() / 2, 0, 0);
		else if (currentTile.x >= 3 && currentTile.x <= 5 && currentTile.y == 0) IMAGEMANAGER->frameRender("��Ʈ1", getMemDC(), ptMouse.x - IMAGEMANAGER->findImage("��Ʈ1")->getFrameWidth() / 4, ptMouse.y - IMAGEMANAGER->findImage("��Ʈ1")->getFrameHeight() / 2, 0, 0);
		else if (currentTile.x >= 6 && currentTile.x <= 8 && currentTile.y == 0) IMAGEMANAGER->frameRender("��Ʈ2", getMemDC(), ptMouse.x - IMAGEMANAGER->findImage("��Ʈ2")->getFrameWidth() / 4, ptMouse.y - IMAGEMANAGER->findImage("��Ʈ1")->getFrameHeight() / 2, 0, 0);
	}
	else if (sampleEnemy)
	{
		if (currentTile.x == 0 && currentTile.y == 0) IMAGEMANAGER->frameRender("�ź���", getMemDC(), ptMouse.x - IMAGEMANAGER->findImage("�ź���")->getFrameWidth() / 2, ptMouse.y - IMAGEMANAGER->findImage("�ź���")->getFrameHeight() / 2 - 13, 0, 0);
		else if (currentTile.x == 1 && currentTile.y == 0) IMAGEMANAGER->frameRender("����", getMemDC(), ptMouse.x - IMAGEMANAGER->findImage("����")->getFrameWidth() / 2, ptMouse.y - IMAGEMANAGER->findImage("����")->getFrameHeight() / 2 - 15, 0, 0);
		else if (currentTile.x == 2 && currentTile.y == 0) IMAGEMANAGER->frameRender("���̰���", getMemDC(), ptMouse.x - IMAGEMANAGER->findImage("���̰���")->getFrameWidth() / 2, ptMouse.y - IMAGEMANAGER->findImage("���̰���")->getFrameHeight() / 2 - 25, 0, 0);
	}

	IMAGEMANAGER->render("���� ��ư", getMemDC(), buttonUI.left, buttonUI.top);
}

//Ÿ�� �����̱�
void mapTool::tileMove()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{

		for (int y = 0; y < TILEY; y++)
		{
			for (int x = 0; x < TILEX; x++)
			{
				tile[y][x].rc.left -= 10;
				tile[y][x].rc.right -= 10;
			}
		}

		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (m_createEnemy[i].enm == ENM_NONE) continue;
			m_createEnemy[i].rc.left -= 10;
			m_createEnemy[i].rc.right -= 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{

		for (int y = 0; y < TILEY; y++)
		{
			for (int x = 0; x < TILEX; x++)
			{
				tile[y][x].rc.top -= 10;
				tile[y][x].rc.bottom -= 10;
			}
		}

		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (m_createEnemy[i].enm == ENM_NONE) continue;
			m_createEnemy[i].rc.top -= 10;
			m_createEnemy[i].rc.bottom -= 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{

		for (int y = 0; y < TILEY; y++)
		{
			for (int x = 0; x < TILEX; x++)
			{
				tile[y][x].rc.left += 10;
				tile[y][x].rc.right += 10;
			}
		}

		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (m_createEnemy[i].enm == ENM_NONE) continue;
			m_createEnemy[i].rc.left += 10;
			m_createEnemy[i].rc.right += 10;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{

		for (int y = 0; y < TILEY; y++)
		{
			for (int x = 0; x < TILEX; x++)
			{
				tile[y][x].rc.top += 10;
				tile[y][x].rc.bottom += 10;
			}
		}

		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (m_createEnemy[i].enm == ENM_NONE) continue;
			m_createEnemy[i].rc.top += 10;
			m_createEnemy[i].rc.bottom += 10;
		}
	}

	//����
	if (tile[0][0].rc.left > 0)
	{
		for (int y = 0; y < TILEY; y++)
		{
			for (int x = 0; x < TILEX; x++)
			{
				if (x == 0)
				{
					tile[y][x].rc.left = 0;
					tile[y][x].rc.right = TILESIZE;
				}
				else
				{
					tile[y][x].rc.left = tile[y][x - 1].rc.right;
					tile[y][x].rc.right = tile[y][x].rc.left + TILESIZE;
				}
			}
		}

		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (m_createEnemy[i].enm == ENM_NONE) continue;
			m_createEnemy[i].rc.left -= 10;
			m_createEnemy[i].rc.right -= 10;
		}
	}
	if (tile[0][0].rc.top > 0)
	{
		for (int y = 0; y < TILEY; y++)
		{
			for (int x = 0; x < TILEX; x++)
			{
				if (y == 0)
				{
					tile[y][x].rc.top = 0;
					tile[y][x].rc.bottom = TILESIZE;
				}
				else
				{
					tile[y][x].rc.top = tile[y - 1][x].rc.bottom;
					tile[y][x].rc.bottom = tile[y][x].rc.top + TILESIZE;
				}
			}
		}

		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (m_createEnemy[i].enm == ENM_NONE) continue;
			m_createEnemy[i].rc.top -= 10;
			m_createEnemy[i].rc.bottom -= 10;
		}
	}
	if (tile[TILEY - 1][TILEX - 1].rc.right < WINSIZEX)
	{
		for (int y = TILEY - 1; y >= 0; y--)
		{
			for (int x = TILEX - 1; x >= 0; x--)
			{
				if (x == TILEX - 1)
				{
					tile[y][x].rc.right = WINSIZEX;
					tile[y][x].rc.left = WINSIZEX - TILESIZE;
				}
				else
				{
					tile[y][x].rc.right = tile[y][x + 1].rc.left;
					tile[y][x].rc.left = tile[y][x].rc.right - TILESIZE;
				}
			}
		}

		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (m_createEnemy[i].enm == ENM_NONE) continue;
			m_createEnemy[i].rc.left += 10;
			m_createEnemy[i].rc.right += 10;
		}
	}
	if (tile[TILEY - 1][TILEX - 1].rc.bottom < WINSIZEY - 192)
	{
		for (int y = TILEY - 1; y >= 0; y--)
		{
			for (int x = TILEX - 1; x >= 0; x--)
			{
				if (y == TILEY - 1)
				{
					tile[y][x].rc.bottom = WINSIZEY - 192;
					tile[y][x].rc.top = WINSIZEY - 192 - TILESIZE;
				}
				else
				{
					tile[y][x].rc.bottom = tile[y + 1][x].rc.top;
					tile[y][x].rc.top = tile[y][x].rc.bottom - TILESIZE;
				}
			}
		}

		for (int i = 0; i < ENEMYMAX; i++)
		{
			if (m_createEnemy[i].enm == ENM_NONE) continue;
			m_createEnemy[i].rc.top += 10;
			m_createEnemy[i].rc.bottom += 10;
		}
	}
}

void mapTool::tileCheck()
{
	for (int y = 0; y < TILEY; y++)
	{
		for (int x = 0; x < TILEX; x++)
		{
			if (tile[y][x].rc.left > WINSIZEX || tile[y][x].rc.top > WINSIZEY - 192 || tile[y][x].rc.right < 0 || tile[y][x].rc.bottom < 0) tileOn[y][x] = false;
			else tileOn[y][x] = true;
		}
	}
}

void mapTool::tileClick()
{
	RECT temp, temp1;

	temp = RectMake(0, WINSIZEY - 192, 960, 192);
	temp1 = RectMake(WINSIZEX - 320, WINSIZEY - 192, 320, 192);
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&temp, ptMouse))//Ÿ�ϼ���
		{
			for (int y = 0; y < SAMPLETILEY; y++)
			{
				for (int x = 0; x < SAMPLETILEX; x++)
				{
					if (PtInRect(&sampleButton[y][x].rcTile, ptMouse))
					{
						currentTile.x = x;
						currentTile.y = y;
						return;
					}
				}
			}
		}
		else if (PtInRect(&temp1, ptMouse))//��ư Ŭ��
		{
			//����
			if (PtInRect(&moveRC[0], ptMouse) && sampleTile)
			{
				for (int i = 0; i < 15; i++)
				{
					moveSample_left();
				}
			}
			//������
			if (PtInRect(&moveRC[1], ptMouse) && sampleTile)
			{
				for (int i = 0; i < 15; i++)
				{
					moveSample_right();
				}
			}
			//Ÿ��
			if (PtInRect(&tileRC, ptMouse))
			{
				for (int y = 0; y < SAMPLETILEY; y++)
				{
					for (int x = 0; x < SAMPLETILEX; x++)
					{
						sampleTile = true;
						sampleObject = false;
						sampleEnemy = false;
						sampleButton[y][x].rcTile = RectMake(TILESIZE * x, WINSIZEY - 192 + y * TILESIZE, TILESIZE, TILESIZE);
						sampleButton[y][x].terrainFrameX = x;
						sampleButton[y][x].terrainFrameY = y;
						currentTileButton = 0;
						ZeroMemory(&currentTile, sizeof(currentTile));
					}
				}
			}
			//������
			if (PtInRect(&exitRC, ptMouse))
			{
				SCENEMANAGER->changeScene("mainMenu");
			}
			//������Ʈ
			if (PtInRect(&objectRC, ptMouse))
			{
				for (int y = 0; y < SAMPLETILEY; y++)
				{
					for (int x = 0; x < SAMPLETILEX; x++)
					{
						sampleTile = false;
						sampleObject = true;
						sampleEnemy = false;
						sampleButton[y][x].rcTile = RectMake(TILESIZE * x, WINSIZEY - 192 + y * TILESIZE, TILESIZE, TILESIZE);
						sampleButton[y][x].terrainFrameX = x;
						sampleButton[y][x].terrainFrameY = y;
						currentTileButton = 0;
						ZeroMemory(&currentTile, sizeof(currentTile));
					}
				}
			}
			//���ʹ�
			if (PtInRect(&enemyRC, ptMouse))
			{
				for (int y = 0; y < SAMPLETILEY; y++)
				{
					for (int x = 0; x < SAMPLETILEX; x++)
					{
						sampleTile = false;
						sampleObject = false;
						sampleEnemy = true;
						sampleButton[y][x].rcTile = RectMake(TILESIZE * x, WINSIZEY - 192 + y * TILESIZE, TILESIZE, TILESIZE);
						sampleButton[y][x].terrainFrameX = x;
						sampleButton[y][x].terrainFrameY = y;
						currentTileButton = 0;
						ZeroMemory(&currentTile, sizeof(currentTile));
					}
				}
			}
		}
		else//Ÿ�Ϻκ�
		{
			if (sampleObject) createObject();
			else if (sampleEnemy) createEnemy();
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (PtInRect(&temp, ptMouse))//Ÿ�ϼ���
		{

		}
		else if (PtInRect(&temp1, ptMouse))//��ư Ŭ��
		{

		}
		else//Ÿ�Ϻκ�
		{
			//Ÿ�� �����
			if (sampleTile)
			{
				for (int y = 0; y < TILEY; y++)
				{
					for (int x = 0; x < TILEX; x++)
					{

						if (PtInRect(&tile[y][x].rc, ptMouse) && tile[y][x].rc.left >= 0 && tile[y][x].rc.top >= 0 && tile[y][x].rc.right <= WINSIZEX && tile[y][x].rc.bottom <= WINSIZEY - 192)
						{
							tile[y][x].terrainFrameX = 0;
							tile[y][x].terrainFrameY = 0;
							return;
						}
					}
				}
			}
			//���ʹ� �����
			if (sampleEnemy)
			{
				for (int i = 0; i < ENEMYMAX; i++)
				{
					if (PtInRect(&m_createEnemy[i].rc, ptMouse) && m_createEnemy[i].rc.left >= 0 && m_createEnemy[i].rc.top >= 0 && m_createEnemy[i].rc.right <= WINSIZEX && m_createEnemy[i].rc.bottom <= WINSIZEY - 192)
					{
						ZeroMemory(&m_createEnemy[i], sizeof(m_createEnemy[i]));

						for (int j = i; j < ENEMYMAX; j++)
						{
							m_createEnemy[j] = m_createEnemy[j + 1];
							if (j == ENEMYMAX - 1) ZeroMemory(&m_createEnemy[j], sizeof(m_createEnemy[j]));
						}
						break;
					}
				}
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&temp, ptMouse))//Ÿ�ϼ���
		{
			/*for (int y = 0; y < TILEY; y++)
			{
			for (int x = 0; x < TILEX; x++)
			{
			if (PtInRect(&tileButton[y][x].rcTile, ptMouse))
			{
			currentTile.x = x;
			currentTile.y = y;
			return;
			}
			}
			}*/
		}
		else if (PtInRect(&temp1, ptMouse))//��ư Ŭ��
		{

		}
		else
		{
			if (sampleTile)
			{
				for (int y = 0; y < TILEY; y++)
				{
					for (int x = 0; x < TILEX; x++)
					{
						if (PtInRect(&tile[y][x].rc, ptMouse) && tile[y][x].rc.left >= 0 && tile[y][x].rc.top >= 0 && tile[y][x].rc.right <= WINSIZEX && tile[y][x].rc.bottom <= WINSIZEY - 192)
						{
							tile[y][x].terrainFrameX = currentTile.x;
							tile[y][x].terrainFrameY = currentTile.y;
						}
					}
				}
			}
		}
	}
}

void mapTool::createObject()
{
	if (sampleObject)
	{
		for (int y = 0; y < TILEY; y++)
		{
			for (int x = 0; x < TILEX; x++)
			{
				if (PtInRect(&tile[y][x].rc, ptMouse))
				{
					if (currentTile.x == 0 && currentTile.y == 0)
					{
						tile[y][x].obj = OBJ_BOX1;
					}
					else if (currentTile.x == 1 && currentTile.y == 0 || currentTile.x == 2 && currentTile.y == 0)
					{
						if (x == TILEX - 1) return;
						tile[y][x].obj = OBJ_BOX2_1;
						tile[y][x + 1].obj = OBJ_BOX2_2;
					}
					else if (currentTile.x >= 3 && currentTile.x <= 5 && currentTile.y == 0)
					{
						if (x >= TILEX - 2) return;
						tile[y][x].obj = OBJ_ROOT1_1;
						tile[y][x + 1].obj = OBJ_ROOT1_2;
						tile[y][x + 2].obj = OBJ_ROOT1_3;
					}
					else if (currentTile.x >= 6 && currentTile.x <= 8 && currentTile.y == 0)
					{
						if (x >= TILEX - 2) return;
						tile[y][x].obj = OBJ_ROOT2_1;
						tile[y][x + 1].obj = OBJ_ROOT2_2;
						tile[y][x + 2].obj = OBJ_ROOT2_3;
					}
				}
			}
		}
	}
}

void mapTool::createEnemy()
{
	if (sampleEnemy)
	{
		if (currentTile.x == 0 && currentTile.y == 0)
		{
			for (int i = 0; i < ENEMYMAX; i++)
			{
				if (m_createEnemy[i].enm != ENM_NONE) continue;

				m_createEnemy[i].enm = ENM_TURTLE;
				m_createEnemy[i].pt = ptMouse;
				m_createEnemy[i].rc = RectMakeCenter(m_createEnemy[i].pt.x, m_createEnemy[i].pt.y, 42, 64);

				break;
			}
		}
		else if (currentTile.x == 1 && currentTile.y == 0)
		{
			for (int i = 0; i < ENEMYMAX; i++)
			{
				if (m_createEnemy[i].enm != ENM_NONE) continue;

				m_createEnemy[i].enm = ENM_DUCK;
				m_createEnemy[i].pt = ptMouse;
				m_createEnemy[i].rc = RectMakeCenter(m_createEnemy[i].pt.x, m_createEnemy[i].pt.y, 38, 60);

				break;
			}
		}
		else if (currentTile.x == 2 && currentTile.y == 0)
		{
			for (int i = 0; i < ENEMYMAX; i++)
			{
				if (m_createEnemy[i].enm != ENM_NONE) continue;

				m_createEnemy[i].enm = ENM_KAMIKAZE;
				m_createEnemy[i].pt = ptMouse;
				m_createEnemy[i].rc = RectMakeCenter(m_createEnemy[i].pt.x, m_createEnemy[i].pt.y, 38, 38);

				break;
			}
		}
	}
}

void mapTool::moveSample_left()
{
	if (currentTileButton <= 0) return;
	currentTileButton--;
	for (int y = 0; y < SAMPLETILEY; y++)
	{
		for (int x = 0; x < SAMPLETILEX; x++)
		{
			sampleButton[y][x].rcTile.left += 64;
			sampleButton[y][x].rcTile.right += 64;
		}
	}
}

void mapTool::moveSample_right()
{
	if (currentTileButton >= 32) return;
	currentTileButton++;
	for (int y = 0; y < SAMPLETILEY; y++)
	{
		for (int x = 0; x < SAMPLETILEX; x++)
		{
			sampleButton[y][x].rcTile.left -= 64;
			sampleButton[y][x].rcTile.right -= 64;
		}
	}
}

void mapTool::saveLoad()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 4; i++)
		{
			if (PtInRect(&saveRC[i], ptMouse))
			{
				HANDLE file;
				DWORD write;
				if (i == 0)
				{
					file = CreateFile("tileMap1.map",
						GENERIC_WRITE,
						0,
						NULL,
						CREATE_ALWAYS,
						FILE_ATTRIBUTE_NORMAL,
						NULL);
				}
				else if (i == 1)
				{
					file = CreateFile("tileMap2.map",
						GENERIC_WRITE,
						0,
						NULL,
						CREATE_ALWAYS,
						FILE_ATTRIBUTE_NORMAL,
						NULL);
				}
				else if (i == 2)
				{
					file = CreateFile("tileMap3.map",
						GENERIC_WRITE,
						0,
						NULL,
						CREATE_ALWAYS,
						FILE_ATTRIBUTE_NORMAL,
						NULL);
				}
				else if (i == 3)
				{
					file = CreateFile("tileMap4.map",
						GENERIC_WRITE,
						0,
						NULL,
						CREATE_ALWAYS,
						FILE_ATTRIBUTE_NORMAL,
						NULL);
				}
				//Ÿ�� ����
				WriteFile(file, tile, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
				//���ʹ� ����
				WriteFile(file, m_createEnemy, sizeof(tagCreateEnemy) * ENEMYMAX, &write, NULL);
				CloseHandle(file);
				break;
			}
			else if (PtInRect(&loadRC[i], ptMouse))
			{
				HANDLE file;
				DWORD read;

				if (i == 0)
				{
					file = CreateFile("tileMap1.map",
						GENERIC_READ,
						0,
						NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						NULL);
				}
				else if (i == 1)
				{
					file = CreateFile("tileMap2.map",
						GENERIC_READ,
						0,
						NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						NULL);
				}
				else if (i == 2)
				{
					file = CreateFile("tileMap3.map",
						GENERIC_READ,
						0,
						NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						NULL);
				}
				else if (i == 3)
				{
					file = CreateFile("tileMap4.map",
						GENERIC_READ,
						0,
						NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						NULL);
				}
				//Ÿ�� �ҷ�����
				ReadFile(file, tile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
				//���ʹ� �ҷ�����
				ReadFile(file, m_createEnemy, sizeof(tagCreateEnemy) * ENEMYMAX, &read, NULL);
				CloseHandle(file);

				for (int y = 0; y < TILEY; y++)
				{
					for (int x = 0; x < TILEX; x++)
					{
						if (tile[y][x].terrainFrameY == 0 || (tile[y][x].terrainFrameX >= 15 && tile[y][x].terrainFrameX <= 18) || (tile[y][x].terrainFrameX >= 25 && tile[y][x].terrainFrameX <= 32) || tile[y][x].terrainFrameX >= 39)
						{
							tile[y][x].terrain = TR_WALL;
						}
						if (tile[y][x].terrain == TR_WALL) tile[y][x].attribute = ATTR_UNMOVE;
					}
				}
				break;
			}
		}
	}
}


void mapTool::pushEnemyMemory()
{
	HANDLE file;
	DWORD read;
	file = CreateFile("tileMap1.map",
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	//Ÿ�� �ҷ�����
	ReadFile(file, tile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, m_createEnemy, sizeof(tagCreateEnemy) * ENEMYMAX, &read, NULL);
	for (int i = 0; i < ENEMYMAX; i++)
	{
		if (m_createEnemy[i].enm == ENM_TURTLE) m_enemyManager->addTurtle(m_createEnemy[i].pt);
		else if (m_createEnemy[i].enm == ENM_DUCK) m_enemyManager->addDuck(m_createEnemy[i].pt);
		else if (m_createEnemy[i].enm == ENM_KAMIKAZE) m_enemyManager->addKamikaze(m_createEnemy[i].pt);
		ZeroMemory(&m_createEnemy[i], sizeof(m_createEnemy[i]));
	}
	CloseHandle(file);
}