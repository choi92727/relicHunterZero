#include "stdafx.h"
#include "mainGame.h"

HINSTANCE hInstance;

HWND hWnd;

POINT ptMouse = { 0, 0 };

mainGame* m_mainGame;

LRESULT CALLBACK WndProc(HWND m_hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

void setWindowSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE m_hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	m_mainGame = new mainGame;

	hInstance = m_hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = m_hInstance;
	wndClass.lpfnWndProc = WNDPROC(WndProc);
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW || CS_VREDRAW;

	RegisterClass(&wndClass);
	hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,
		WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY,
		NULL,
		(HMENU)NULL,
		m_hInstance,
		NULL);

	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	ShowWindow(hWnd, nCmdShow);

	if (FAILED(m_mainGame->init()))
	{
		return 0;
	}

	MSG message;

	//while (GetMessage(&message, 0, 0, 0))
	//{
	//	TranslateMessage(&message);
	//	DispatchMessage(&message);
	//}

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60);
			m_mainGame->update();
			m_mainGame->render();
		}
	}

	m_mainGame->release();

	UnregisterClass(WINNAME, m_hInstance);

	return message.wParam;
}



LRESULT CALLBACK WndProc(HWND m_hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return m_mainGame->MainProc(m_hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, WINSTYLE, false);
	SetWindowPos(hWnd, NULL, x, y, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);
}
