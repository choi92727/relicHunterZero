#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
{
}


selectScene::~selectScene()
{
}

HRESULT selectScene::init()
{
	IMAGEMANAGER->addImage("���ù��", "Images/selectBg.bmp", 1280, 720);
	IMAGEMANAGER->addImage("���ú�", "Images/selectStarPattern.bmp", 98, 98);
	IMAGEMANAGER->addImage("���������", "Images/selectTopBar.bmp", 467, 46,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����߰���", "Images/selectMiddleBar.bmp", 1280, 90, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̼���", "Images/jimmySelectBar.bmp", 5440, 72, 17, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̴�����", "Images/riderSelectBar.bmp", 5440, 72, 17, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ī��", "Images/card_jimmy.bmp", 500, 281, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̴�ī��", "Images/card_red.bmp", 500, 281, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "Images/selectStart.bmp", 229, 43, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "Images/selectedStart.bmp", 229, 43, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ٲٱ���", "Images/selectChange.bmp", 229, 43, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ٲٱ���", "Images/selectedChange.bmp", 229, 43, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ڷΰ���", "Images/selectCancel.bmp", 243, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޴���", "Images/spr_menu_star.bmp", 37, 40, true, RGB(255, 0, 255));
	loopX = loopY = 0;

	select_Rc[0] = RectMakeCenter(320, WINSIZEY / 4, 320, 72);
	select_Rc[1] = RectMakeCenter(960, WINSIZEY / 4, 320, 72);

	start_Rc = RectMake(453, 632, 229, 43);
	chage_Rc = RectMake(611, 669, 229, 43);
	cancel_Rc= RectMake(40, WINSIZEY-64, 229, 43);
	im_rider = IMAGEMANAGER->findImage("���̴�����");
	im_jimmy = IMAGEMANAGER->findImage("���̼���");

	int arrLen[] = { 5 };
	ANIMATIONMANAGER->addAnimation("jimmy0", "���̼���", arrLen, 1, 5, false);
	ANIMATIONMANAGER->addAnimation("rider0", "���̴�����", arrLen, 1, 5, false);
	int arrLen1[] = { 0,1,2,3,4 };
	ANIMATIONMANAGER->addAnimation("jimmy1", "���̼���", arrLen1, 5, 9, false);
	ANIMATIONMANAGER->addAnimation("rider1", "���̴�����", arrLen1, 5, 9, false);
	int arrLen2[] = { 6,7,8,9,10,11,12,13,14,15,16 };
	ANIMATIONMANAGER->addAnimation("jimmy2", "���̼���", arrLen2, 11, 9, false);
	ANIMATIONMANAGER->addAnimation("rider2", "���̴�����", arrLen2, 11, 9, false);
	ani_rider = ANIMATIONMANAGER->findAnimation("rider0");
	ani_jimmy = ANIMATIONMANAGER->findAnimation("jimmy0");

	s_Ct = non_selected;
	return S_OK;
}

void selectScene::release()
{
}

void selectScene::update()
{
	moveStar();
	aniSelectBar();

}

void selectScene::render()
{
	RECT allRC = RectMake(0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("���ù��", getMemDC());
	IMAGEMANAGER->loopAlphaRender("���ú�", getMemDC(), &allRC, loopX, loopY, 125);
	IMAGEMANAGER->render("�����߰���", getMemDC(), 0, 170);
	IMAGEMANAGER->render("���������", getMemDC(), 0, 50);
	im_jimmy->aniRender(getMemDC(), select_Rc[0].left, select_Rc[0].top, ani_jimmy);
	im_rider->aniRender(getMemDC(), select_Rc[1].left, select_Rc[1].top, ani_rider);
	IMAGEMANAGER->render("�ڷΰ���", getMemDC(), cancel_Rc.left, cancel_Rc.top);
	switch (s_Ct)
	{
	case non_selected:
		if (PtInRect(&cancel_Rc, ptMouse))
		{
			IMAGEMANAGER->render("�޴���", getMemDC(), cancel_Rc.left+100, cancel_Rc.top-20);//18,20
		}
		break;
	case jimmy_selected:
		IMAGEMANAGER->render("����ī��", getMemDC(), 330, 369);
		renderCardBar();
		break;
	case rider_selected:
		IMAGEMANAGER->render("���̴�ī��", getMemDC(), 330, 369);
		renderCardBar();
		break;
	}
	
}

void selectScene::moveStar()
{
	loopX--;
	loopY--;
}

void selectScene::aniSelectBar()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		switch (s_Ct)
		{
		case non_selected:
			if (PtInRect(&select_Rc[0], ptMouse))
			{
				s_Ct = jimmy_selected;
				ANIMATIONMANAGER->start("jimmy1");
			}

			if (PtInRect(&select_Rc[1], ptMouse))
			{
				s_Ct = rider_selected;
				ANIMATIONMANAGER->start("rider1");
			}
			if (PtInRect(&cancel_Rc, ptMouse))
			{
				SCENEMANAGER->changeScene("mainMenu");
			}
			break;
		case jimmy_selected:
			clickCardBar();
			ani_jimmy = ANIMATIONMANAGER->findAnimation("jimmy0");
			s_Ct = non_selected;
			break;
		case rider_selected:
			clickCardBar();
			ani_rider = ANIMATIONMANAGER->findAnimation("rider0");
			s_Ct = non_selected;
			break;
		}
	}
	switch (s_Ct)
	{
	case non_selected:
		if (PtInRect(&select_Rc[0], ptMouse))
		{
			if (ani_jimmy != ANIMATIONMANAGER->findAnimation("jimmy2"))
			{
				ani_jimmy = ANIMATIONMANAGER->findAnimation("jimmy2");
				ANIMATIONMANAGER->start("jimmy2");
			}
		}
		else
		{
			ani_jimmy = ANIMATIONMANAGER->findAnimation("jimmy0");
		}
		if (PtInRect(&select_Rc[1], ptMouse))
		{
			if (ani_rider != ANIMATIONMANAGER->findAnimation("rider2"))
			{
				ani_rider = ANIMATIONMANAGER->findAnimation("rider2");
				ANIMATIONMANAGER->start("rider2");
			}
		}
		else
		{
			ani_rider = ANIMATIONMANAGER->findAnimation("rider0");
		}

		break;
	case jimmy_selected:
		ani_jimmy = ANIMATIONMANAGER->findAnimation("jimmy1");
		break;
	case rider_selected:
		ani_rider = ANIMATIONMANAGER->findAnimation("rider1");
		break;
	}
}

void selectScene::renderCardBar()
{
	if (PtInRect(&start_Rc, ptMouse))
	{
		IMAGEMANAGER->render("������", getMemDC(), start_Rc.left, start_Rc.top);
		IMAGEMANAGER->render("�ٲٱ���", getMemDC(), chage_Rc.left, chage_Rc.top);
	}
	else if (PtInRect(&chage_Rc, ptMouse))
	{
		IMAGEMANAGER->render("������", getMemDC(), start_Rc.left, start_Rc.top);
		IMAGEMANAGER->render("�ٲٱ���", getMemDC(), chage_Rc.left, chage_Rc.top);
	}
	else
	{
		IMAGEMANAGER->render("������", getMemDC(), start_Rc.left, start_Rc.top);
		IMAGEMANAGER->render("�ٲٱ���", getMemDC(), chage_Rc.left, chage_Rc.top);
	}
}

void selectScene::clickCardBar()
{
	if (PtInRect(&chage_Rc, ptMouse))
	{
		s_Ct = non_selected;
	}
	else if (PtInRect(&start_Rc, ptMouse))
	{
		if (s_Ct == jimmy_selected)//���̰� ���õ��� 
		{
			s_Ct = non_selected;
		}
		else if (s_Ct == rider_selected)//���̴��� ���õ���
		{
			s_Ct = non_selected;
		}
	}
}


