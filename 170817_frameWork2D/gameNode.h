#pragma once
#include "image.h"


//����� �̹����� ����ƽ���� ����
static image* m_backBuffer = IMAGEMANAGER->addImage("backbuffer", WINSIZEX, WINSIZEY);

//�������� ����� ��Ʈ�� �̳ѹ�

class gameNode
{
private:
	HDC m_hdc;
	bool m_managerInit;
	
public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render();

	image* getBackBuffer() { return m_backBuffer; }

	//�޸� DC ���
	HDC getMemDC() { return m_backBuffer->getMemDC(); }
	//HDC ���
	HDC getHDC() { return m_hdc; }
	void DrawPng(Image* tempImage, Graphics* graphics, int x, int y, int sizeX, int sizeY, float angle); //��ο��Լ�


	//���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

