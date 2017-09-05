#include "stdafx.h"
#include "addImage.h"


addImage::addImage()
{
}


addImage::~addImage()
{
}

HRESULT addImage::init()
{
	//¸ÊÅø
	IMAGEMANAGER->addFrameImage("¸ÊÅø", "Images/¸ÊÅø.bmp", 3008, 192, 47, 3);
	IMAGEMANAGER->addImage("¸ÊÅø ¹öÆ°", "Images/¸ÊÅø ¹öÆ°.bmp", 320, 192);

	//¿ÀºêÁ§Æ®
	IMAGEMANAGER->addFrameImage("¹Ú½º1", "Images/spr_crate.bmp", 444, 112, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¹Ú½º2", "Images/spr_longbox.bmp", 444, 112, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("·çÆ®1", "Images/spr_root1.bmp", 762, 134, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("·çÆ®2", "Images/spr_root2.bmp", 762, 134, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("¹Ú½º1 ÆÄ±«", "Images/spr_crate_break.bmp", 2552, 130, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¹Ú½º2 ÆÄ±«", "Images/spr_longbox_break.bmp", 2784, 130, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("·çÆ®1 ÆÄ±«", "Images/spr_root1_break.bmp", 3048, 134, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("·çÆ®2 ÆÄ±«", "Images/spr_root2_break.bmp", 2286, 134, 9, 1, true, RGB(255, 0, 255));

	//Ç¥ÁöÆÇ
	IMAGEMANAGER->addFrameImage("¹æÇâ Ç¥ÁöÆÇ", "Images/notice_move.bmp", 3520, 86, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Æ©Åä¸®¾ó Ç¥ÁöÆÇ", "Images/notice_tutorial.bmp", 2784, 70, 16, 1, true, RGB(255, 0, 255));

	//ÇÃ·¹ÀÌ¾î
	IMAGEMANAGER->addFrameImage("Áö¹Ì", "Images/jimmy.bmp", 1368, 846, 12, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¶óÀÌ´õ", "Images/rider.bmp", 2736, 896, 24, 8, true, RGB(255, 0, 255));

	//¿¡³Ê¹Ì
	IMAGEMANAGER->addFrameImage("°¡¹Ì°¡Á¦", "Images/°¡¹Ì°¡Á¦.bmp", 1824, 940, 16, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("°ÅºÏÀÌ", "Images/°ÅºÏÀÌ.bmp", 1596, 752, 14, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¿À¸®", "Images/¿À¸®.bmp", 1482, 940, 13, 10, true, RGB(255, 0, 255));

	//ÃÑ
	IMAGEMANAGER->addImage("±ÇÃÑ", "Images/spr_pistol_jimmy_0.bmp", 60, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¸Ó½Å°Ç", "Images/spr_machinegun_0.bmp", 60, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼¦°Ç", "Images/spr_shotgun_0.bmp", 64, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ÇÃ¶óÁî¸¶", "Images/spr_smg_plasma_0.bmp", 60, 26, true, RGB(255, 0, 255));

	//ºÒ·¿
	IMAGEMANAGER->addImage("±âº» ÃÑ¾Ë", "Images/spr_bullet_small_1.bmp", 46, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("¼¦°Ç ÃÑ¾Ë", "Images/spr_bullet_1.bmp", 46, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÇÃ¶óÁî¸¶ ÃÑ¾Ë", "Images/spr_plasmarbullet.bmp", 552, 30, 12, 1, true, RGB(255, 0, 255));


	IMAGEMANAGER->
	return S_OK;
}
