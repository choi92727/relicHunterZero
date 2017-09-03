#include "stdafx.h"
#include "mainMenu.h"


mainMenu::mainMenu()
{
}


mainMenu::~mainMenu()
{
}

HRESULT mainMenu::init()
{
	IMAGEMANAGER->addImage("메인메뉴배경화면", "images/bg_menu_main.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메뉴바", "images/menuBar.bmp", 477, 54, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메뉴바선택", "images/menuBar_aft.bmp", 530, 54, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메뉴별", "images/spr_menu_star.bmp", 37, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("별패턴", "images/starPattern.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("전메뉴바텍스트", "images/menu_pre_text.bmp", 218, 216, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("후메뉴바텍스트", "images/menu_aft_text.bmp", 218, 216, 1, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("메인로고", "images/mainMenu_logo.bmp",22890,243,42,1,true, RGB(255, 0, 255));
	//right-41,top+6

	m_Bar[0].pre_Select = RectMake(0, 359, 474, 54);
	m_Bar[1].pre_Select = RectMake(-80, 459, 474, 54);
	m_Bar[2].pre_Select = RectMake(-160, 559, 474, 54);
	m_Bar[3].pre_Select = RectMake(-240, 659, 474, 54);

	m_Bar[0].aft_Select = RectMake(0, 359, 530, 54);
	m_Bar[1].aft_Select = RectMake(-80, 459, 530, 54);
	m_Bar[2].aft_Select = RectMake(-160, 559, 530, 54);
	m_Bar[3].aft_Select = RectMake(-240, 659, 530, 54);
	loopx = 0;
	loopy = 0;
	for (int i = 0; i < 4; i++)
		m_Bar[i].selected = false;

	mainLogo = IMAGEMANAGER->findImage("메인로고");
	ANIMATIONMANAGER->addDefAnimation("logo_ani1", "메인로고", 10, false, false);
	ANIMATIONMANAGER->start("logo_ani1");
	mainLogo_Ani = ANIMATIONMANAGER->findAnimation("logo_ani1");
	return S_OK;
}

void mainMenu::release()
{
}

void mainMenu::update()
{
	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(&m_Bar[i].pre_Select, ptMouse))
		{
			m_Bar[i].selected = true;
		}
		else
		{
			m_Bar[i].selected = false;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (m_Bar[0].selected)//게임시작
		{
			SCENEMANAGER->changeScene("loadingGame");
		}
		else if (m_Bar[1].selected)//맵툴
		{
			SCENEMANAGER->changeScene("mapTool");
			
		}
		else if (m_Bar[2].selected)//credit
		{
			SCENEMANAGER->changeScene("creditScene");
		}
		else if (m_Bar[3].selected)//게임종료
		{
			PostQuitMessage(0);
		}
	}
	loopx++;
	loopy++;
}

void mainMenu::render()
{
	int pre_x,aft_x;
	RECT allRC = RectMake(0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("메인메뉴배경화면", getMemDC());
	
	IMAGEMANAGER->loopAlphaRender("별패턴", getMemDC(), &allRC, loopx, loopy,125);
	for (int i = 0; i < 4; i++)
	{
		if (m_Bar[i].selected)
		{
			if (i == 0)
			{
				aft_x = 100;
			}
			else if (i == 1)
			{
				aft_x = 60;
			}
			else if (i == 2)
			{
				aft_x = 40;
			}
			else
			{
				aft_x = -10;
			}
			IMAGEMANAGER->render("메뉴바선택", getMemDC(), m_Bar[i].aft_Select.left, m_Bar[i].aft_Select.top);
			IMAGEMANAGER->frameRender("후메뉴바텍스트", getMemDC(), aft_x, m_Bar[i].aft_Select.top, 0, i);
			IMAGEMANAGER->render("메뉴별",getMemDC(), m_Bar[i].aft_Select.right-41, m_Bar[i].aft_Select.top+6);
		}
		else
		{
			if (i == 0)
			{
				pre_x = 100;
			}
			else if (i == 1)
			{
				pre_x = 60;
			}
			else if (i == 2)
			{
				pre_x = 40;
			}
			else
			{
				pre_x = -10;
			}
			IMAGEMANAGER->render("메뉴바", getMemDC(), m_Bar[i].pre_Select.left, m_Bar[i].pre_Select.top);
			IMAGEMANAGER->frameRender("전메뉴바텍스트", getMemDC(), pre_x, m_Bar[i].pre_Select.top, 0, i);
			IMAGEMANAGER->render("메뉴별", getMemDC(), m_Bar[i].pre_Select.right - 41, m_Bar[i].pre_Select.top + 6);
		}
	}
	mainLogo->aniRender(getMemDC(), -10, 100, mainLogo_Ani);
}
