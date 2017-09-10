#include "stdafx.h"
#include "addSounds.h"


addSounds::addSounds()
{
}


addSounds::~addSounds()
{
}

HRESULT addSounds::init()
{
	//브금들
	SOUNDMANAGER->addSound("로딩브금", "sounds/bgm_intro.mp3", true, true);//로딩화면 브금
	SOUNDMANAGER->addSound("메인메뉴브금", "sounds/bgm_main.mp3", true, true);//메인메뉴 브금
	SOUNDMANAGER->addSound("선택메뉴브금", "sounds/bgm_menu.mp3", true, true);//캐릭선택화면 브금
	SOUNDMANAGER->addSound("할아버지의11월", "sounds/할아버지.mp3", true, true);//맵툴브금
	SOUNDMANAGER->addSound("테란브금", "sounds/StarcraftTerran.mp3", true, true);//크레딧 브금
	SOUNDMANAGER->addSound("우주선", "sounds/bgm_main.wav", true, true);//우주선 브금
	SOUNDMANAGER->addSound("스테이지1", "sounds/bgm_stage1.mp3", true, true);//스테이지1 브금
	SOUNDMANAGER->addSound("스테이지2", "sounds/bgm_stage2.mp3", true, true);//스테이지2 브금
	SOUNDMANAGER->addSound("스테이지3", "sounds/bgm_stage3.mp3", true, true);//스테이지3 브금

																		 //메뉴이펙트
	SOUNDMANAGER->addSound("메뉴클릭", "sounds/sfx_menu_click.wav", false, false);
	SOUNDMANAGER->addSound("메뉴마우스", "sounds/sfx_menu_mouse.wav", false, false);

	//에너미
	SOUNDMANAGER->addSound("거북이_피격", "sounds/sfx_turtle_hit.wav", false, false);
	SOUNDMANAGER->addSound("거북이_죽음", "sounds/sfx_turtle_death.wav", false, false);

	SOUNDMANAGER->addSound("오리_죽음", "sounds/sfx_duck_death.wav", false, false);
	SOUNDMANAGER->addSound("오리_대쉬", "sounds/sfx_dash1.wav", false, false);

	SOUNDMANAGER->addSound("가미가제_피격", "sounds/sfx_kami_hit1.wav", false, false);
	SOUNDMANAGER->addSound("가미가제_죽음", "sounds/sfx_kami_death.wav", false, false);
	SOUNDMANAGER->addSound("가미가제_대쉬", "sounds/sfx_kami_dash.wav", false, false);


	//플레이어 및 무기 사운드
	SOUNDMANAGER->addSound("사망", "sounds/플레이어사망.wav", false, false);

	SOUNDMANAGER->addSound("대쉬", "sounds/대쉬.wav", false, false);
	SOUNDMANAGER->addSound("걷기", "sounds/걷기.wav", false, true);
	SOUNDMANAGER->addSound("달리기시작", "sounds/달리기시작시.wav", false, false);
	SOUNDMANAGER->addSound("달리기중", "sounds/달리기.wav", false, false);

	SOUNDMANAGER->addSound("피격", "sounds/피격.wav", false, false);
	SOUNDMANAGER->addSound("쉴드피격", "sounds/쉴드피격.wav", false, false);
	SOUNDMANAGER->addSound("쉴드깨짐", "sounds/쉴드깨짐.wav", false, false);
	SOUNDMANAGER->addSound("쉴드리젠", "sounds/쉴드리젠시작.wav", false, true);

	SOUNDMANAGER->addSound("텔레포트", "sounds/텔레포트.wav", false, false);

	SOUNDMANAGER->addSound("장전", "sounds/장전.wav", false, false);
	SOUNDMANAGER->addSound("권총", "sounds/권총과머신건.wav", false, false);
	SOUNDMANAGER->addSound("머신건", "sounds/권총과머신건.wav", false, true);
	SOUNDMANAGER->addSound("샷건", "sounds/샷건.wav", false, false);
	SOUNDMANAGER->addSound("플라즈마건", "sounds/플라즈마건.wav", false, false);
	return S_OK;
}
