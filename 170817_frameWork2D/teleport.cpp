#include "stdafx.h"
#include "teleport.h"


teleport::teleport()
{
}


teleport::~teleport()
{
}

HRESULT teleport::init()
{
	IMAGEMANAGER->addImage("���θ޴����ȭ��", "images/bg_menu_main.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	m_rc = RectMakeCenter(WINSIZEX/2, WINSIZEY/2, 150, 100);
	m_im = IMAGEMANAGER->findImage("�ڷ���Ʈ����Ʈ");
	frameX = 0;
	ANIMATIONMANAGER->addDefAnimation("�ڷ���Ʈ�ִ�", "�ڷ���Ʈ����Ʈ", 10, false, true);
	m_ani = ANIMATIONMANAGER->findAnimation("�ڷ���Ʈ�ִ�");
	ANIMATIONMANAGER->start("�ڷ���Ʈ�ִ�");
	return S_OK;
}

void teleport::release()
{
}

void teleport::update()
{
	//frameX=10;
}

void teleport::render()
{
	IMAGEMANAGER->render("���θ޴����ȭ��", getMemDC());
	m_im->aniAlphaRender(getMemDC(), m_rc.left, m_rc.top, m_ani,100);
	
	IMAGEMANAGER->render("�ڷ���Ʈ", getMemDC(), m_rc.left, m_rc.top);
}
