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
	IMAGEMANAGER->addFrameImage("오브젝트", "Images/오브젝트.bmp", 704, 64, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("에너미", "Images/에너미.bmp", 192, 64, 3, 1, true, RGB(255, 0, 255));

	//맵툴 버튼
	IMAGEMANAGER->addImage("맵툴 버튼", "Images/맵툴 버튼.bmp", 320, 192);

	//오브젝트
	IMAGEMANAGER->addFrameImage("박스1", "Images/spr_crate.bmp", 444, 130, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("박스2", "Images/spr_longbox.bmp", 444, 130, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("루트1", "Images/spr_root1.bmp", 762, 134, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("루트2", "Images/spr_root2.bmp", 762, 134, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("텔레포트", "Images/텔레포트.bmp", 150, 100, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("박스1 파괴", "Images/spr_crate_break.bmp", 2552, 130, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("박스2 파괴", "Images/spr_longbox_break.bmp", 2552, 130, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("루트1 파괴", "Images/spr_root1_break.bmp", 3048, 134, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("루트2 파괴", "Images/spr_root2_break.bmp", 2286, 134, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("텔레포트이펙트", "Images/텔레포트이펙트 사본.bmp", 2550, 100, 17, 1, true, RGB(255, 0, 255));

	ANIMATIONMANAGER->addDefAnimation("텔포애니", "텔레포트이펙트", 10, false, true);

	//표지판
	IMAGEMANAGER->addFrameImage("방향 표지판", "Images/notice_move.bmp", 3520, 86, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("튜토리얼 표지판", "Images/notice_tutorial.bmp", 2784, 70, 16, 1, true, RGB(255, 0, 255));

	//플레이어 UI
	IMAGEMANAGER->addFrameImage("지미_얼굴", "Images/jimmyMark.bmp", 288, 81, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("라이더_얼굴", "Images/riderMark.bmp", 279, 81, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("체력바_하트", "Images/hpBar_heart.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("실드바_실드", "Images/shieldBar_shield.bmp", 14, 14, true, RGB(255, 0, 255));

	//플레이어
	IMAGEMANAGER->addFrameImage("지미", "Images/jimmy.bmp", 1368, 1692, 12, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("라이더", "Images/rider.bmp", 2736, 1792, 24, 16, true, RGB(255, 0, 255));

	//에너미
	IMAGEMANAGER->addFrameImage("에너미_탐지", "Images/exclamation.bmp", 126, 34, 7, 1, true, RGB(255, 0, 255));
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
	IMAGEMANAGER->addFrameImage("플라즈마 총알", "Images/spr_plasmarbullet.bmp", 1104, 60, 12, 1, true, RGB(255, 0, 255));


	//숫자
	IMAGEMANAGER->addFrameImage("별숫자", "Images/starNumber.bmp", 150, 22, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("총알숫자", "Images/bulletNubmer.bmp", 260, 37, 10, 1, true, RGB(255, 0, 255));

	//실루엣
	IMAGEMANAGER->addImage("권총실루엣", "Images/spr_pistol_jimmy_2.bmp", 120, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("머신건실루엣", "Images/spr_machinegun_2.bmp", 60, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("샷건실루엣", "Images/spr_shotgun_2.bmp", 64, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플라즈마실루엣", "Images/spr_smg_plasma_2.bmp", 60, 26, true, RGB(255, 0, 255));

	// 총기 애니메이션(플라즈마)
	ANIMATIONMANAGER->addDefAnimation("plasma", "플라즈마 총알", 10, false, true);

	//체력바
	IMAGEMANAGER->addImage("체력바앞", "Images/hpBarFront.bmp", 168, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("체력바뒤", "Images/hpBarBack.bmp", 168, 48, true, RGB(255, 0, 255));
	//쉴드바
	IMAGEMANAGER->addImage("쉴드바앞", "Images/shieldBarFront.bmp", 154, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쉴드바뒤", "Images/shieldBarBack.bmp", 154, 25, true, RGB(255, 0, 255));
	//스테미너바
	IMAGEMANAGER->addImage("스테미너바앞", "Images/staminaBarFront.bmp", 153, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스테미너바뒤", "Images/staminaBarBack.bmp", 153, 6, true, RGB(255, 0, 255));

	//체력얼굴
	IMAGEMANAGER->addFrameImage("지미상태얼굴", "Images/jimmyMark.bmp", 288, 81, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("라이더상태얼굴", "Images/riderMark.bmp", 229, 81, 3, 1, true, RGB(255, 0, 255));

	//아이템
	IMAGEMANAGER->addFrameImage("주울수있다", "Images/canGetItem.bmp", 240, 38, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아모0", "Images/spr_pickup_ammo_0.bmp", 30, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아모1", "Images/spr_pickup_ammo_1.bmp", 30, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아모2", "Images/spr_pickup_ammo_2.bmp", 30, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("체력", "Images/spr_pickup_drop_0.bmp", 30, 29, true, RGB(255, 0, 255));


	//배경
	IMAGEMANAGER->addImage("배경1", "Images/stage2.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경2", "Images/stage3.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("배경3", "Images/stage4.bmp", 1280, 720, true, RGB(255, 0, 255));

	//쉴드
	IMAGEMANAGER->addFrameImage("쉴드", "Images/shield.bmp", 684, 94, 6, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("쉴드0", "Images/shield0.bmp", 42, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쉴드1", "Images/shield1.bmp", 42, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쉴드2", "Images/shield2.bmp", 42, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쉴드3", "Images/shield3.bmp", 42, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쉴드4", "Images/shield4.bmp", 42, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쉴드5", "Images/shield5.bmp", 42, 46, true, RGB(255, 0, 255));

	return S_OK;
}
