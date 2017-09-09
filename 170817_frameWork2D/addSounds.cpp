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

	//메뉴이펙트
	SOUNDMANAGER->addSound("메뉴클릭", "sounds/sfx_menu_click.wav", false, false);
	SOUNDMANAGER->addSound("메뉴마우스", "sounds/sfx_menu_mouse.wav", false, false);





	return S_OK;
}
