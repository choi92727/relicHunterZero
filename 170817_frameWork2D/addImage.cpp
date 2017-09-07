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
	//����
	IMAGEMANAGER->addFrameImage("����", "Images/����.bmp", 3008, 192, 47, 3);
	IMAGEMANAGER->addFrameImage("������Ʈ", "Images/������Ʈ.bmp", 576, 64, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ʹ�", "Images/���ʹ�.bmp", 192, 64, 3, 1, true, RGB(255, 0, 255));

	//���� ��ư
	IMAGEMANAGER->addImage("���� ��ư", "Images/���� ��ư.bmp", 320, 192);

	//������Ʈ
	IMAGEMANAGER->addFrameImage("�ڽ�1", "Images/spr_crate.bmp", 444, 112, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ڽ�2", "Images/spr_longbox.bmp", 444, 112, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ1", "Images/spr_root1.bmp", 762, 134, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ2", "Images/spr_root2.bmp", 762, 134, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ڷ���Ʈ","Images/teleport.bmp", 150, 100,true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("�ڽ�1 �ı�", "Images/spr_crate_break.bmp", 2552, 130, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ڽ�2 �ı�", "Images/spr_longbox_break.bmp", 2784, 130, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ1 �ı�", "Images/spr_root1_break.bmp", 3048, 134, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ2 �ı�", "Images/spr_root2_break.bmp", 2286, 134, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ڷ���Ʈ����Ʈ", "Images/�ڷ���Ʈ����Ʈ �纻.bmp", 2550, 100, 17, 1, true, RGB(255, 0, 255));

	//ǥ����
	IMAGEMANAGER->addFrameImage("���� ǥ����", "Images/notice_move.bmp", 3520, 86, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ʃ�丮�� ǥ����", "Images/notice_tutorial.bmp", 2784, 70, 16, 1, true, RGB(255, 0, 255));

	//�÷��̾�
	IMAGEMANAGER->addFrameImage("����", "Images/jimmy.bmp", 1368, 1692, 12, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̴�", "Images/rider.bmp", 2736, 1792, 24, 16, true, RGB(255, 0, 255));

	//���ʹ�
	IMAGEMANAGER->addFrameImage("���̰���", "Images/���̰���.bmp", 1824, 940, 16, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ź���", "Images/�ź���.bmp", 1596, 752, 14, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", "Images/����.bmp", 1482, 940, 13, 10, true, RGB(255, 0, 255));

	//��
	IMAGEMANAGER->addImage("����", "Images/spr_pistol_jimmy_0.bmp", 60, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ӽŰ�", "Images/spr_machinegun_0.bmp", 60, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����", "Images/spr_shotgun_0.bmp", 64, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ö��", "Images/spr_smg_plasma_0.bmp", 60, 26, true, RGB(255, 0, 255));

	//�ҷ�
	IMAGEMANAGER->addImage("�⺻ �Ѿ�", "Images/spr_bullet_small_1.bmp", 46, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���� �Ѿ�", "Images/spr_bullet_1.bmp", 46, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ö�� �Ѿ�", "Images/spr_plasmarbullet.bmp", 552, 30, 12, 1, true, RGB(255, 0, 255));

	//����
	IMAGEMANAGER->addFrameImage("�Ѿ˼���", "Images/bulletNubmer.bmp", 260, 37, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "Images/starNumber.bmp", 150, 22, 10, 1, true, RGB(255, 0, 255));

	return S_OK;
}
