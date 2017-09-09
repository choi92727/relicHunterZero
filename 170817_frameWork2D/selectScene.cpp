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
	IMAGEMANAGER->addImage("����ī��", "Images/card_red.bmp", 500, 281, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ĵ��", "Images/selectCancel.bmp", 243, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�������", "Images/start_chage_bar.bmp", 916, 43,4,1 ,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ĵ����", "Images/spr_menu_star.bmp", 37, 40, true, RGB(255, 0, 255));
	
	
	loopX = loopY = 0;

	select_Rc[0] = RectMakeCenter(320, WINSIZEY / 4, 320, 72);
	select_Rc[1] = RectMakeCenter(960, WINSIZEY / 4, 320, 72);
	cancel_Rc= RectMake(30, WINSIZEY -64, 243, 64);
	start_Rc = RectMake(459, 634, 229, 43);
	change_Rc = RectMake(614, 671, 229, 43);

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

	startX = 0;
	changeX = 2;
		
	SOUNDMANAGER->play("���ø޴����", 0.1f);
	return S_OK;
}

void selectScene::release()
{
	SOUNDMANAGER->stop("���ø޴����");
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
	IMAGEMANAGER->render("ĵ��",getMemDC(), cancel_Rc.left, cancel_Rc.top);
	im_jimmy->aniRender(getMemDC(), select_Rc[0].left, select_Rc[0].top, ani_jimmy);
	im_rider->aniRender(getMemDC(), select_Rc[1].left, select_Rc[1].top, ani_rider);
	selectRender();
	
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
				SOUNDMANAGER->play("�޴�Ŭ��", 1.0f);
				s_Ct = jimmy_selected;
				ANIMATIONMANAGER->start("jimmy1");
			}

			if (PtInRect(&select_Rc[1], ptMouse))
			{
				SOUNDMANAGER->play("�޴�Ŭ��", 1.0f);
				s_Ct = rider_selected;
				ANIMATIONMANAGER->start("rider1");
			}
			if (PtInRect(&cancel_Rc, ptMouse))
			{
				SOUNDMANAGER->play("�޴�Ŭ��", 1.0f);
				SCENEMANAGER->changeScene("mainMenu");
			}
			break;
		case jimmy_selected:
			if (PtInRect(&start_Rc, ptMouse))
			{
				SOUNDMANAGER->play("�޴�Ŭ��", 1.0f);
				goJimmy();
				
			}
			else if (PtInRect(&change_Rc, ptMouse))
			{
				SOUNDMANAGER->play("�޴�Ŭ��", 1.0f);
			}
			ani_jimmy = ANIMATIONMANAGER->findAnimation("jimmy0");
			s_Ct = non_selected;
			break;
		case rider_selected:
			if (PtInRect(&start_Rc, ptMouse))
			{
				SOUNDMANAGER->play("�޴�Ŭ��", 1.0f);
				goRider();
			}
			else if (PtInRect(&change_Rc, ptMouse))
			{
				SOUNDMANAGER->play("�޴�Ŭ��", 1.0f);
			}
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
				SOUNDMANAGER->play("�޴����콺", 1.0f);
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
			SOUNDMANAGER->play("�޴����콺", 1.0f);
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

void selectScene::selectRender()
{
	
	if (PtInRect(&start_Rc, ptMouse))
	{
		if(!(startX == 1&& changeX == 2))
		SOUNDMANAGER->play("�޴����콺", 1.0f);
		startX = 1;
		changeX = 2;
	}
	else if (PtInRect(&change_Rc, ptMouse))
	{
		if (!(startX == 0 && changeX == 3))
		SOUNDMANAGER->play("�޴����콺", 1.0f);
		startX = 0;
		changeX = 3;
	}
	else
	{
		startX = 0;
		changeX = 2;
	}
	switch (s_Ct)
	{
	case non_selected:
		if (PtInRect(&cancel_Rc, ptMouse))
		{
			IMAGEMANAGER->render("ĵ����", getMemDC(), cancel_Rc.left + (cancel_Rc.right - cancel_Rc.left) / 2 - 18, cancel_Rc.top - 20);
		}
		break;
	case jimmy_selected:
		IMAGEMANAGER->render("����ī��", getMemDC(), 389, 366);
		IMAGEMANAGER->frameRender("�������", getMemDC(), start_Rc.left, start_Rc.top, startX,0);
		IMAGEMANAGER->frameRender("�������", getMemDC(), change_Rc.left, change_Rc.top, changeX,0);
		break;
	case rider_selected:
		IMAGEMANAGER->render("����ī��", getMemDC(), 389, 366);
		IMAGEMANAGER->frameRender("�������", getMemDC(), start_Rc.left, start_Rc.top, startX, 0);
		IMAGEMANAGER->frameRender("�������", getMemDC(), change_Rc.left, change_Rc.top, changeX, 0);
		break;
	}
}

void selectScene::goJimmy()
{
	SCENEMANAGER->changeScene("stageScene");//���̰� ���õǰ� ȭ����ȯ
}

void selectScene::goRider()
{
	SCENEMANAGER->changeScene("mapTool");//���̴��� ���õǰ� ȭ����ȯ
}
