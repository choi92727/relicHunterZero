#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}

gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	m_hdc = GetDC(hWnd);
	m_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	m_hdc = GetDC(hWnd);
	m_managerInit = managerInit;

	if (managerInit)
	{
		SetTimer(hWnd, 1, 10, NULL);	//Ÿ�̸� �ʱ�ȭ
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		SCENEMANAGER->init();
		SOUNDMANAGER->init();

	}

	return S_OK;
}

void gameNode::release()
{

	if (m_managerInit)
	{
		//Ÿ�̸� ����
		KillTimer(hWnd, 1);
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		RND->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
	}
	//DC ����
	ReleaseDC(hWnd, m_hdc);
}

void gameNode::update()
{
	//���߿� ���� Ÿ�̸Ӹ� ���� �Ŀ��� ������� ����
	//������۸� ���� ������� �ʴ´�.(true -> false)
	InvalidateRect(hWnd, NULL, false);
}

void gameNode::render()
{
}



LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		ptMouse.x = LOWORD(lParam);
		ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void gameNode::DrawPng(Image * tempImage, Graphics * graphics, int x, int y, int sizeX, int sizeY, float angle)
{
	Image* img = tempImage;
	Matrix matrix;
	matrix.RotateAt(angle*(180 / PI), Gdiplus::PointF((float)(x + sizeX / 2), (float)(y + sizeY / 2)));
	graphics->SetTransform(&matrix);
	graphics->DrawImage(img, x, y, sizeX, sizeY);
	img = NULL;
	SAFE_DELETE(img);
}

void gameNode::DrawPng(Image * tempImage, Graphics * graphics, int x, int y, int sizeX, int sizeY, float angle, int addAngle)
{
	Image* img = tempImage;
	Matrix matrix;
	matrix.RotateAt(addAngle + angle*(180 / PI), Gdiplus::PointF((float)(x + sizeX / 2), (float)(y + sizeY / 2)));
	graphics->SetTransform(&matrix);
	graphics->DrawImage(img, x, y, sizeX, sizeY);
	img = NULL;
	SAFE_DELETE(img);
}

