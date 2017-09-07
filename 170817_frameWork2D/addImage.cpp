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
	//맵툴
	IMAGEMANAGER->addFrameImage("맵툴", "Images/맵툴.bmp", 3008, 192, 47, 3);
	IMAGEMANAGER->addFrameImage("오브젝트", "Images/오브젝트.bmp", 576, 64, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("에너미", "Images/에너미.bmp", 192, 64, 3, 1, true, RGB(255, 0, 255));

	//맵툴 버튼
	IMAGEMANAGER->addImage("맵툴 버튼", "Images/맵툴 버튼.bmp", 320, 192);

	//오브젝트
	IMAGEMANAGER->addFrameImage("박스1", "Images/spr_crate.bmp", 444, 112, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("박스2", "Images/spr_longbox.bmp", 444, 112, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("루트1", "Images/spr_root1.bmp", 762, 134, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("루트2", "Images/spr_root2.bmp", 762, 134, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("텔레포트","Images/teleport.bmp", 150, 100,true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("박스1 파괴", "Images/spr_crate_break.bmp", 2552, 130, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("박스2 파괴", "Images/spr_longbox_break.bmp", 2784, 130, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("루트1 파괴", "Images/spr_root1_break.bmp", 3048, 134, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("루트2 파괴", "Images/spr_root2_break.bmp", 2286, 134, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("텔레포트이펙트", "Images/텔레포트이펙트 사본.bmp", 2550, 100, 17, 1, true, RGB(255, 0, 255));

	//표지판
	IMAGEMANAGER->addFrameImage("방향 표지판", "Images/notice_move.bmp", 3520, 86, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("튜토리얼 표지판", "Images/notice_tutorial.bmp", 2784, 70, 16, 1, true, RGB(255, 0, 255));

	//플레이어
	IMAGEMANAGER->addFrameImage("지미", "Images/jimmy.bmp", 1368, 1692, 12, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("라이더", "Images/rider.bmp", 2736, 1792, 24, 16, true, RGB(255, 0, 255));

	//에너미
	IMAGEMANAGER->addFrameImage("가미가제", "Images/가미가제.bmp", 1824, 940, 16, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("거북이", "Images/거북이.bmp", 1596, 752, 14, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("오리", "Images/오리.bmp", 1482, 940, 13, 10, true, RGB(255, 0, 255));

	//총
	IMAGEMANAGER->addImage("권총", "Images/spr_pistol_jimmy_0.bmp", 60, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("머신건", "Images/spr_machinegun_0.bmp", 60, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("샷건", "Images/spr_shotgun_0.bmp", 64, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플라즈마", "Images/spr_smg_plasma_0.bmp", 60, 26, true, RGB(255, 0, 255));

	//불렛
	IMAGEMANAGER->addImage("기본 총알", "Images/spr_bullet_small_1.bmp", 46, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("샷건 총알", "Images/spr_bullet_1.bmp", 46, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("플라즈마 총알", "Images/spr_plasmarbullet.bmp", 552, 30, 12, 1, true, RGB(255, 0, 255));

	//숫자
	IMAGEMANAGER->addFrameImage("총알숫자", "Images/bulletNubmer.bmp", 260, 37, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("별숫자", "Images/starNumber.bmp", 150, 22, 10, 1, true, RGB(255, 0, 255));

	return S_OK;
}
