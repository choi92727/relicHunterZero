// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

// C++ 런타임 헤더 파일입니다.
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <ole2.h> 
#pragma comment(lib, "gdiplus")
#include <GdiPlus.h>


//===================================================
// ## 내가 만든 헤더파일 이 곳에 추가 ##
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
// ## 싱글톤 추가 ##
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
// ## 네임스페이스 추가 ##
//===================================================
using namespace MY_UTIL;
using namespace Gdiplus;

//===================================================
// ## 디파인문 추가 ## (윈도우 초기화 셋팅)
//===================================================
#define WINNAME LPTSTR(TEXT("1704기 11class"))
#define WINSTARTX 100
#define WINSTARTY 100
#define WINSIZEX 1280
#define WINSIZEY 720
//600
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//===================================================
// ## 매크로 함수 ## (메인 게임의 릴리즈 부분에서 사용)
//===================================================
#define SAFE_DELETE(p) {if(p) {delete(p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p) = nullptr;}}

//===================================================
// ## 전역 변수 ## (인스턴스, 핸들, 마우스좌표)
//===================================================
extern HINSTANCE hInstance;
extern HWND hWnd;
extern POINT ptMouse;

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
