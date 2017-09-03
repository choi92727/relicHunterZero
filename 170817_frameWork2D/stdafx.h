// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

// C++ ��Ÿ�� ��� �����Դϴ�.
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <ole2.h> 
#pragma comment(lib, "gdiplus")
#include <GdiPlus.h>


//===================================================
// ## ���� ���� ������� �� ���� �߰� ##
//===================================================
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "util.h"
#include "imageManager.h"
#include "timeManager.h"
#include "txtData.h"
#include "sceneManager.h"
#include "soundManager.h"
#include "effectManager.h"
#include "animationManager.h"
#include "tags.h"

//===================================================
// ## �̱��� �߰� ##
//===================================================
#define KEYMANAGER keyManager::getSingleton()
#define RND randomFunction::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define SCENEMANAGER  sceneManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define ANIMATIONMANAGER animationManager::getSingleton()

//===================================================
// ## ���ӽ����̽� �߰� ##
//===================================================
using namespace MY_UTIL;
using namespace Gdiplus;

//===================================================
// ## �����ι� �߰� ## (������ �ʱ�ȭ ����)
//===================================================
#define WINNAME LPTSTR(TEXT("1704�� 11class"))
#define WINSTARTX 100
#define WINSTARTY 100
#define WINSIZEX 1280
#define WINSIZEY 720
//600
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//===================================================
// ## ��ũ�� �Լ� ## (���� ������ ������ �κп��� ���)
//===================================================
#define SAFE_DELETE(p) {if(p) {delete(p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p) = nullptr;}}

//===================================================
// ## ���� ���� ## (�ν��Ͻ�, �ڵ�, ���콺��ǥ)
//===================================================
extern HINSTANCE hInstance;
extern HWND hWnd;
extern POINT ptMouse;

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
