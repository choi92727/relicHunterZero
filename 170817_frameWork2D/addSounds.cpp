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
	//��ݵ�
	SOUNDMANAGER->addSound("�ε����", "sounds/bgm_intro.mp3", true, true);//�ε�ȭ�� ���
	SOUNDMANAGER->addSound("���θ޴����", "sounds/bgm_main.mp3", true, true);//���θ޴� ���
	SOUNDMANAGER->addSound("���ø޴����", "sounds/bgm_menu.mp3", true, true);//ĳ������ȭ�� ���
	SOUNDMANAGER->addSound("�Ҿƹ�����11��", "sounds/�Ҿƹ���.mp3", true, true);//�������
	SOUNDMANAGER->addSound("�׶����", "sounds/StarcraftTerran.mp3", true, true);//ũ���� ���

	//�޴�����Ʈ
	SOUNDMANAGER->addSound("�޴�Ŭ��", "sounds/sfx_menu_click.wav", false, false);
	SOUNDMANAGER->addSound("�޴����콺", "sounds/sfx_menu_mouse.wav", false, false);





	return S_OK;
}
