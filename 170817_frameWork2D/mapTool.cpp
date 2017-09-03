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
			tileButton[y][x].rcTile = RectMake(TILESIZE * x, WINSIZEY - 192 + y * TILESIZE, TILESIZE, TILESIZE);
			tileButton[y][x].terrainFrameX = x;
			tileButton[y][x].terrainFrameY = y;
		}
	}
	currentTileButton = 0;
	buttonUI = RectMake(WINSIZEX - 320, WINSIZEY - 192, 320, 192);
	for (int i = 0; i < 2; i++)
	{
		selectRC[i] = RectMake(WINSIZEX - 320 + i * 160, WINSIZEY - 144, 160, 48);
	}
	for (int i = 0; i < 4; i++)
	{
		moveRC[i] = RectMake(WINSIZEX - 320 + i * 80, WINSIZEY - 192, 80, 48);
	}
	for (int i = 0; i < 4; i++)
	{
		saveRC[i] = RectMake(WINSIZEX - 320 + i * 80, WINSIZEY - 96, 80, 48);
		loadRC[i] = RectMake(WINSIZEX - 320 + i * 80, WINSIZEY - 48, 80, 48);
	}
	loookSample = false;
	sampleX = 0;
	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	tileMove();
	tileCheck();
	tileClick();
	saveLoad();
	if (KEYMANAGER->isOnceKeyDown('S'))//샘플박스 보이기
	{
		loookSample = !loookSample;
	}
	if (KEYMANAGER->isOnceKeyDown('L'))//샘플박스 보이기
	{
		moveSample_right();
	}
	if (KEYMANAGER->isOnceKeyDown('K'))//샘플박스 보이기
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
				IMAGEMANAGER->frameRender("맵툴", getMemDC(), tile[y][x].rc.left, tile[y][x].rc.top, tile[y][x].terrainFrameX, tile[y][x].terrainFrameY);
				if (tile[y][x].terrain == TR_NONE)
				{
					sprintf(str, "%d, %d", x, y);
					
				}
				else
				{
					IMAGEMANAGER->frameRender("맵툴", getMemDC(), tile[y][x].rc.left, tileButton[y][x].rcTile.top, tile[y][x].terrainFrameX, tile[y][x].terrainFrameY);

				}
				if (loookSample)
				{
					Rectangle(getMemDC(), tile[y][x].rc.left, tile[y][x].rc.top, tile[y][x].rc.right, tile[y][x].rc.bottom);
					TextOut(getMemDC(), tile[y][x].rc.left + 20, tile[y][x].rc.top + 10, str, strlen(str));
				}
			}
		}
	}
	
	for (int y = 0; y < SAMPLETILEY; y++)//SAMPLE
	{
		for (int x = sampleX; x < SAMPLETILEX+ sampleX; x++)
		{
			if (currentTileButton <= x && x < currentTileButton + 15)
			{
				Rectangle(getMemDC(), tileButton[y][x].rcTile.left, tileButton[y][x].rcTile.top, tileButton[y][x].rcTile.right, tileButton[y][x].rcTile.bottom);
				IMAGEMANAGER->frameRender("맵툴", getMemDC(), tileButton[y][x].rcTile.left, tileButton[y][x].rcTile.top, tileButton[y][x].terrainFrameX, tileButton[y][x].terrainFrameY);
			}
		}
	}
	IMAGEMANAGER->frameRender("맵툴", getMemDC(), ptMouse.x - TILESIZE / 2, ptMouse.y - TILESIZE / 2, currentTile.x, currentTile.y);
	IMAGEMANAGER->render("맵툴 버튼", getMemDC(), buttonUI.left, buttonUI.top);
}

//타일 움직이기
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
	}

	//고정
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
	RECT temp,temp1;

	temp = RectMake(0, WINSIZEY - 192, 960, 192);
	temp1= RectMake(WINSIZEX - 320, WINSIZEY - 192, 320,192);
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&temp, ptMouse))//타일선택
		{
			for (int y = 0; y < SAMPLETILEY; y++)
			{
				for (int x = 0; x < SAMPLETILEX; x++)
				{
					if (PtInRect(&tileButton[y][x].rcTile, ptMouse))
					{
						currentTile.x = x;
						currentTile.y = y;
						return;
					}
				}
			}
		}
		else if (PtInRect(&temp1, ptMouse))//버튼 클릭
		{
			
			if (PtInRect(&moveRC[1], ptMouse))
			{
				for (int i = 0; i < 15; i++)
				{
					moveSample_right();
				}
			}
			if (PtInRect(&moveRC[0], ptMouse))
			{
				for (int i = 0; i < 15; i++)
				{
					moveSample_left();
				}
			}
			if (PtInRect(&moveRC[2], ptMouse))//tile버튼
			{
				
			}
			if (PtInRect(&selectRC[0], ptMouse))//object버튼
			{
				
			}
			if (PtInRect(&selectRC[1], ptMouse))//enermy버튼
			{
				
				
			}
			if (PtInRect(&moveRC[3], ptMouse))
			{
				SCENEMANAGER->changeScene("mainMenu");
			}
		}
		else//타일부분
		{
			for (int y = 0; y < TILEY; y++)
			{
				for (int x = 0; x < TILEX; x++)
				{
					
					if (PtInRect(&tile[y][x].rc, ptMouse) && tile[y][x].rc.left >= 0 && tile[y][x].rc.top >= 0 && tile[y][x].rc.right <= WINSIZEX && tile[y][x].rc.bottom <= WINSIZEY - 192)
					{
						tile[y][x].terrainFrameX = currentTile.x;
						tile[y][x].terrainFrameY = currentTile.y;
						return;
					}
				}
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (PtInRect(&temp, ptMouse))//타일선택
		{
			
		}
		else if (PtInRect(&temp1, ptMouse))//버튼 클릭
		{

		}
		else//타일부분
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
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&temp, ptMouse))//타일선택
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
		else if (PtInRect(&temp1, ptMouse))//버튼 클릭
		{

		}
		else {
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

void mapTool::moveSample_left()
{
	if (currentTileButton <= 0)
		return;
	currentTileButton--;
	for (int y = 0; y < SAMPLETILEY; y++)
	{
		for (int x = 0; x < SAMPLETILEX; x++)
		{
			tileButton[y][x].rcTile.left += 64;
			tileButton[y][x].rcTile.right += 64;
		}
	}
}

void mapTool::moveSample_right()
{
	if (currentTileButton >= 32)
		return;
	currentTileButton++;
	for (int y = 0; y < SAMPLETILEY; y++)
	{
		for (int x = 0; x < SAMPLETILEX; x++)
		{
			tileButton[y][x].rcTile.left -= 64;
			tileButton[y][x].rcTile.right -= 64;
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

				WriteFile(file, tile, sizeof(tagTile) * TILEX * TILEY, &write, NULL);
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

				ReadFile(file, tile, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
				CloseHandle(file);

				for (int y = 0; y < TILEY; y++)
				{
					for (int x = 0; x < TILEX; x++)
					{
						if (tile[y][x].terrainFrameY == 0 ||( tile[y][x].terrainFrameX >= 15 && tile[y][x].terrainFrameX <= 18) || (tile[y][x].terrainFrameX >= 25 && tile[y][x].terrainFrameX <= 32) || tile[y][x].terrainFrameX >= 39)
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
