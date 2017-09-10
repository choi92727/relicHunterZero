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
	SOUNDMANAGER->addSound("���ּ�", "sounds/bgm_main.wav", true, true);//���ּ� ���
	SOUNDMANAGER->addSound("��������1", "sounds/bgm_stage1.mp3", true, true);//��������1 ���
	SOUNDMANAGER->addSound("��������2", "sounds/bgm_stage2.mp3", true, true);//��������2 ���
	SOUNDMANAGER->addSound("��������3", "sounds/bgm_stage3.mp3", true, true);//��������3 ���

																		 //�޴�����Ʈ
	SOUNDMANAGER->addSound("�޴�Ŭ��", "sounds/sfx_menu_click.wav", false, false);
	SOUNDMANAGER->addSound("�޴����콺", "sounds/sfx_menu_mouse.wav", false, false);

	//���ʹ�
	SOUNDMANAGER->addSound("�ź���_�ǰ�", "sounds/sfx_turtle_hit.wav", false, false);
	SOUNDMANAGER->addSound("�ź���_����", "sounds/sfx_turtle_death.wav", false, false);

	SOUNDMANAGER->addSound("����_����", "sounds/sfx_duck_death.wav", false, false);
	SOUNDMANAGER->addSound("����_�뽬", "sounds/sfx_dash1.wav", false, false);

	SOUNDMANAGER->addSound("���̰���_�ǰ�", "sounds/sfx_kami_hit1.wav", false, false);
	SOUNDMANAGER->addSound("���̰���_����", "sounds/sfx_kami_death.wav", false, false);
	SOUNDMANAGER->addSound("���̰���_�뽬", "sounds/sfx_kami_dash.wav", false, false);


	//�÷��̾� �� ���� ����
	SOUNDMANAGER->addSound("���", "sounds/�÷��̾���.wav", false, false);

	SOUNDMANAGER->addSound("�뽬", "sounds/�뽬.wav", false, false);
	SOUNDMANAGER->addSound("�ȱ�", "sounds/�ȱ�.wav", false, true);
	SOUNDMANAGER->addSound("�޸������", "sounds/�޸�����۽�.wav", false, false);
	SOUNDMANAGER->addSound("�޸�����", "sounds/�޸���.wav", false, false);

	SOUNDMANAGER->addSound("�ǰ�", "sounds/�ǰ�.wav", false, false);
	SOUNDMANAGER->addSound("�����ǰ�", "sounds/�����ǰ�.wav", false, false);
	SOUNDMANAGER->addSound("�������", "sounds/�������.wav", false, false);
	SOUNDMANAGER->addSound("���帮��", "sounds/���帮������.wav", false, true);

	SOUNDMANAGER->addSound("�ڷ���Ʈ", "sounds/�ڷ���Ʈ.wav", false, false);

	SOUNDMANAGER->addSound("����", "sounds/����.wav", false, false);
	SOUNDMANAGER->addSound("����", "sounds/���Ѱ��ӽŰ�.wav", false, false);
	SOUNDMANAGER->addSound("�ӽŰ�", "sounds/���Ѱ��ӽŰ�.wav", false, true);
	SOUNDMANAGER->addSound("����", "sounds/����.wav", false, false);
	SOUNDMANAGER->addSound("�ö����", "sounds/�ö����.wav", false, false);
	return S_OK;
}
