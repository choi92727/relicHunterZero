#pragma once
#include "image.h"


//백버퍼 이미지를 스태틱으로 변경
static image* m_backBuffer = IMAGEMANAGER->addImage("backbuffer", WINSIZEX, WINSIZEY);

//맵툴에서 사용할 컨트롤 이넘문

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

	//메모리 DC 얻기
	HDC getMemDC() { return m_backBuffer->getMemDC(); }
	//HDC 얻기
	HDC getHDC() { return m_hdc; }


	//메인 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	void DrawPng(Image* tempImage, Graphics* graphics, int x, int y, int sizeX, int sizeY, float angle); //시범용 드로우함수 복붙용
	void DrawPng(Image* tempImage, Graphics* graphics, int x, int y, int sizeX, int sizeY, float angle,int addAngle); //시범용 드로우함수 복붙용
	//void DrawPng(Image* tempImag, Graphics* graphics, int x, int y, int sizeX, int sizeY);
};

