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
	IMAGEMANAGER->addFrameImage("������Ʈ", "Images/������Ʈ.bmp", 704, 64, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ʹ�", "Images/���ʹ�.bmp", 192, 64, 3, 1, true, RGB(255, 0, 255));

	//���� ��ư
	IMAGEMANAGER->addImage("���� ��ư", "Images/���� ��ư.bmp", 320, 192);

	//������Ʈ
	IMAGEMANAGER->addFrameImage("�ڽ�1", "Images/spr_crate.bmp", 444, 130, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ڽ�2", "Images/spr_longbox.bmp", 444, 130, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ1", "Images/spr_root1.bmp", 762, 134, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ2", "Images/spr_root2.bmp", 762, 134, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ڷ���Ʈ", "Images/�ڷ���Ʈ.bmp", 150, 100, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("�ڽ�1 �ı�", "Images/spr_crate_break.bmp", 2552, 130, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ڽ�2 �ı�", "Images/spr_longbox_break.bmp", 2552, 130, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ1 �ı�", "Images/spr_root1_break.bmp", 3048, 134, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ2 �ı�", "Images/spr_root2_break.bmp", 2286, 134, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ڷ���Ʈ����Ʈ", "Images/�ڷ���Ʈ����Ʈ �纻.bmp", 2550, 100, 17, 1, true, RGB(255, 0, 255));

	ANIMATIONMANAGER->addDefAnimation("�����ִ�", "�ڷ���Ʈ����Ʈ", 10, false, true);

	//ǥ����
	IMAGEMANAGER->addFrameImage("���� ǥ����", "Images/notice_move.bmp", 3520, 86, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ʃ�丮�� ǥ����", "Images/notice_tutorial.bmp", 2784, 70, 16, 1, true, RGB(255, 0, 255));

	//�÷��̾� UI
	IMAGEMANAGER->addFrameImage("����_��", "Images/jimmyMark.bmp", 288, 81, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̴�_��", "Images/riderMark.bmp", 279, 81, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ü�¹�_��Ʈ", "Images/hpBar_heart.bmp", 20, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ǵ��_�ǵ�", "Images/shieldBar_shield.bmp", 14, 14, true, RGB(255, 0, 255));

	//�÷��̾�
	IMAGEMANAGER->addFrameImage("����", "Images/jimmy.bmp", 1368, 1692, 12, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̴�", "Images/rider.bmp", 2736, 1792, 24, 16, true, RGB(255, 0, 255));

	//���ʹ�
	IMAGEMANAGER->addFrameImage("���ʹ�_Ž��", "Images/exclamation.bmp", 126, 34, 7, 1, true, RGB(255, 0, 255));
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
	IMAGEMANAGER->addFrameImage("�ö�� �Ѿ�", "Images/spr_plasmarbullet.bmp", 1104, 60, 12, 1, true, RGB(255, 0, 255));


	//����
	IMAGEMANAGER->addFrameImage("������", "Images/starNumber.bmp", 150, 22, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ѿ˼���", "Images/bulletNubmer.bmp", 260, 37, 10, 1, true, RGB(255, 0, 255));

	//�Ƿ翧
	IMAGEMANAGER->addImage("���ѽǷ翧", "Images/spr_pistol_jimmy_2.bmp", 120, 44, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ӽŰǽǷ翧", "Images/spr_machinegun_2.bmp", 60, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ǽǷ翧", "Images/spr_shotgun_2.bmp", 64, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�ö���Ƿ翧", "Images/spr_smg_plasma_2.bmp", 60, 26, true, RGB(255, 0, 255));

	// �ѱ� �ִϸ��̼�(�ö��)
	ANIMATIONMANAGER->addDefAnimation("plasma", "�ö�� �Ѿ�", 10, false, true);

	//ü�¹�
	IMAGEMANAGER->addImage("ü�¹پ�", "Images/hpBarFront.bmp", 168, 48, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ü�¹ٵ�", "Images/hpBarBack.bmp", 168, 48, true, RGB(255, 0, 255));
	//�����
	IMAGEMANAGER->addImage("����پ�", "Images/shieldBarFront.bmp", 154, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ٵ�", "Images/shieldBarBack.bmp", 154, 25, true, RGB(255, 0, 255));
	//���׹̳ʹ�
	IMAGEMANAGER->addImage("���׹̳ʹپ�", "Images/staminaBarFront.bmp", 153, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���׹̳ʹٵ�", "Images/staminaBarBack.bmp", 153, 6, true, RGB(255, 0, 255));

	//ü�¾�
	IMAGEMANAGER->addFrameImage("���̻��¾�", "Images/jimmyMark.bmp", 288, 81, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̴����¾�", "Images/riderMark.bmp", 229, 81, 3, 1, true, RGB(255, 0, 255));

	//������
	IMAGEMANAGER->addFrameImage("�ֿ���ִ�", "Images/canGetItem.bmp", 240, 38, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ƹ�0", "Images/spr_pickup_ammo_0.bmp", 30, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ƹ�1", "Images/spr_pickup_ammo_1.bmp", 30, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ƹ�2", "Images/spr_pickup_ammo_2.bmp", 30, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ü��", "Images/spr_pickup_drop_0.bmp", 30, 29, true, RGB(255, 0, 255));


	//���
	IMAGEMANAGER->addImage("���1", "Images/stage2.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���2", "Images/stage3.bmp", 1280, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���3", "Images/stage4.bmp", 1280, 720, true, RGB(255, 0, 255));

	//����
	IMAGEMANAGER->addFrameImage("����", "Images/shield.bmp", 684, 94, 6, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("����0", "Images/shield0.bmp", 42, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����1", "Images/shield1.bmp", 42, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����2", "Images/shield2.bmp", 42, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����3", "Images/shield3.bmp", 42, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����4", "Images/shield4.bmp", 42, 46, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����5", "Images/shield5.bmp", 42, 46, true, RGB(255, 0, 255));

	return S_OK;
}
