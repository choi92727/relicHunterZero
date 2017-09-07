#include "stdafx.h"
#include "image.h"
#pragma comment(lib,"msimg32.lib")	//알프블렌드를 사용하기위해서 라이브러리 추가

/*
참고 ) 이미지 파일 포맷
1. BMP
제약이 많지만 무손실 무압축이므로 속도가 가장 빠르다.

2. JPG
손실 압축이므로 원래 가진 이미지의 손실이 일어나는 대신
어떠한 알고리즘에 의해 압축이 되어 용량이 작다.

3. PNG
1,2 번과 달리 alpha(반투명) 채널이 없다.
*/

image::image()
	:m_imageInfo(nullptr)
	, m_fileName(nullptr)
	, m_isTrans(NULL)
	, m_transColor(RGB(0, 0, 0))
	, m_blendImage(nullptr)
{
}

image::~image()
{
}

HRESULT image::init(int width, int height)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 잇다면 릴리즈 먼저 해줄것
	if (m_imageInfo != nullptr) release();

	//DC 가져오기(현재 윈도우에 대한 화면DC를 임시로 받아옴)
	HDC hdc = GetDC(hWnd);

	//CreateCompatibleDC
	//비트맵을 출력하기 위해서 메모리DC를 만들어 주는 함수
	//화면 DC와 메모리 DC 호환
	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵을 생성해 주는 함수
	//SelectObject
	//기본의 비트맵 핸들을 반환하고, 새로운 비트맵을 메모리 DC가 선택하고
	//메모리 DC에 비트맵이 그려짐, 화면 DC 아니므로 모리터에 출력 x

	//이미지 정보 생성하기
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_EMPTY;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->width = width;
	m_imageInfo->height = height;

	//파일이름
	m_fileName = nullptr;

	//투명키 컬러 셋팅
	m_isTrans = false;
	m_transColor = RGB(0, 0, 0);

	//알파블렌드 옵션
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.AlphaFormat = 0;	//32비트인경우 AC_SRC_APLHA를 지정하고 그 외에는 0으로 지정함(그렇지 않으면 알파블렌딩을 함수 사용 불가)
	m_blendFunc.BlendOp = AC_SRC_OVER;

	//알파블렌드를 사용하기 위한 이미지 초기화
	m_blendImage = new IMAGE_INFO;
	m_blendImage->loadType = LOAD_EMPTY;
	m_blendImage->resID = 0;
	m_blendImage->hMemDC = CreateCompatibleDC(hdc);
	m_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, m_imageInfo->width, m_imageInfo->height);
	m_blendImage->hOBit = (HBITMAP)SelectObject(m_blendImage->hMemDC, m_blendImage->hBit);
	m_blendImage->width = WINSIZEX;
	m_blendImage->height = WINSIZEY;


	//리소스를 얻어오는데 실패 했을때
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 잇다면 릴리즈 먼저 해줄것
	if (m_imageInfo != nullptr) release();

	//DC 가져오기(현재 윈도우에 대한 화면DC를 임시로 받아옴)
	HDC hdc = GetDC(hWnd);

	//CreateCompatibleDC
	//비트맵을 출력하기 위해서 메모리DC를 만들어 주는 함수
	//화면 DC와 메모리 DC 호환
	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵을 생성해 주는 함수
	//SelectObject
	//기본의 비트맵 핸들을 반환하고, 새로운 비트맵을 메모리 DC가 선택하고
	//메모리 DC에 비트맵이 그려짐, 화면 DC 아니므로 모리터에 출력 x

	//이미지 정보 생성하기
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_RESOURCE;
	m_imageInfo->resID = resID;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)LoadBitmap(hInstance, MAKEINTRESOURCE(m_imageInfo->resID));//파일을 비트맵에 올린다.
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->width = width;
	m_imageInfo->height = height;

	//파일이름
	m_fileName = nullptr;

	//투명키 컬러 셋팅
	m_isTrans = isTrans;
	m_transColor = transColor;

	//리소스를 얻어오는데 실패 했을때
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 잇다면 릴리즈 먼저 해줄것
	if (m_imageInfo != nullptr) release();

	//DC 가져오기(현재 윈도우에 대한 화면DC를 임시로 받아옴)
	HDC hdc = GetDC(hWnd);

	//CreateCompatibleDC
	//비트맵을 출력하기 위해서 메모리DC를 만들어 주는 함수
	//화면 DC와 메모리 DC 호환
	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵을 생성해 주는 함수
	//SelectObject
	//기본의 비트맵 핸들을 반환하고, 새로운 비트맵을 메모리 DC가 선택하고
	//메모리 DC에 비트맵이 그려짐, 화면 DC 아니므로 모리터에 출력 x

	//이미지 정보 생성하기
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_FILE;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)LoadImage(hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->width = width;
	m_imageInfo->height = height;

	//파일 이름
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	m_isTrans = isTrans;
	m_transColor = transColor;

	//알파블렌드 옵션
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.AlphaFormat = 0;	//32비트인경우 AC_SRC_APLHA를 지정하고 그 외에는 0으로 지정함(그렇지 않으면 알파블렌딩을 함수 사용 불가)
	m_blendFunc.BlendOp = AC_SRC_OVER;

	//알파블렌드를 사용하기 위한 이미지 초기화
	m_blendImage = new IMAGE_INFO;
	m_blendImage->loadType = LOAD_FILE;
	m_blendImage->resID = 0;
	m_blendImage->hMemDC = CreateCompatibleDC(hdc);
	m_blendImage->hBit = (HBITMAP)LoadImage(hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_blendImage->hOBit = (HBITMAP)SelectObject(m_blendImage->hMemDC, m_blendImage->hBit);
	m_blendImage->width = WINSIZEX;
	m_blendImage->height = WINSIZEY;

	//리소스를 얻어오는데 실패 했을때
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 잇다면 릴리즈 먼저 해줄것
	if (m_imageInfo != nullptr) release();

	//DC 가져오기(현재 윈도우에 대한 화면DC를 임시로 받아옴)
	HDC hdc = GetDC(hWnd);

	//CreateCompatibleDC
	//비트맵을 출력하기 위해서 메모리DC를 만들어 주는 함수
	//화면 DC와 메모리 DC 호환
	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵을 생성해 주는 함수
	//SelectObject
	//기본의 비트맵 핸들을 반환하고, 새로운 비트맵을 메모리 DC가 선택하고
	//메모리 DC에 비트맵이 그려짐, 화면 DC 아니므로 모리터에 출력 x

	//이미지 정보 생성하기
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_FILE;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)LoadImage(hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->x = x - (width / 2);
	m_imageInfo->y = y - (height / 2);
	m_imageInfo->width = width;
	m_imageInfo->height = height;

	//파일 이름
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	m_isTrans = isTrans;
	m_transColor = transColor;

	//알파블렌드 옵션
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.AlphaFormat = 0;	//32비트인경우 AC_SRC_APLHA를 지정하고 그 외에는 0으로 지정함(그렇지 않으면 알파블렌딩을 함수 사용 불가)
	m_blendFunc.BlendOp = AC_SRC_OVER;

	//알파블렌드를 사용하기 위한 이미지 초기화
	m_blendImage = new IMAGE_INFO;
	m_blendImage->loadType = LOAD_FILE;
	m_blendImage->resID = 0;
	m_blendImage->hMemDC = CreateCompatibleDC(hdc);
	m_blendImage->hBit = (HBITMAP)LoadImage(hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_blendImage->hOBit = (HBITMAP)SelectObject(m_blendImage->hMemDC, m_blendImage->hBit);
	m_blendImage->width = WINSIZEX;
	m_blendImage->height = WINSIZEY;

	//리소스를 얻어오는데 실패 했을때
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 잇다면 릴리즈 먼저 해줄것
	if (m_imageInfo != nullptr) release();

	//DC 가져오기(현재 윈도우에 대한 화면DC를 임시로 받아옴)
	HDC hdc = GetDC(hWnd);

	//CreateCompatibleDC
	//비트맵을 출력하기 위해서 메모리DC를 만들어 주는 함수
	//화면 DC와 메모리 DC 호환
	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵을 생성해 주는 함수
	//SelectObject
	//기본의 비트맵 핸들을 반환하고, 새로운 비트맵을 메모리 DC가 선택하고
	//메모리 DC에 비트맵이 그려짐, 화면 DC 아니므로 모리터에 출력 x

	//이미지 정보 생성하기
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_FILE;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)LoadImage(hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->width = width;
	m_imageInfo->height = height;
	m_imageInfo->maxFrameX = frameX - 1;
	m_imageInfo->maxFrameY = frameY - 1;
	m_imageInfo->frameWidth = width / frameX;
	m_imageInfo->frameHeight = height / frameY;

	//파일 이름
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	m_isTrans = isTrans;
	m_transColor = transColor;

	//알파블렌드 옵션
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.AlphaFormat = 0;	//32비트인경우 AC_SRC_APLHA를 지정하고 그 외에는 0으로 지정함(그렇지 않으면 알파블렌딩을 함수 사용 불가)
	m_blendFunc.BlendOp = AC_SRC_OVER;

	//알파블렌드를 사용하기 위한 이미지 초기화
	m_blendImage = new IMAGE_INFO;
	m_blendImage->loadType = LOAD_FILE;
	m_blendImage->resID = 0;
	m_blendImage->hMemDC = CreateCompatibleDC(hdc);
	m_blendImage->hBit = (HBITMAP)LoadImage(hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_blendImage->hOBit = (HBITMAP)SelectObject(m_blendImage->hMemDC, m_blendImage->hBit);
	m_blendImage->width = WINSIZEX;
	m_blendImage->height = WINSIZEY;

	//리소스를 얻어오는데 실패 했을때
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보에 값이 들어 잇다면 릴리즈 먼저 해줄것
	if (m_imageInfo != nullptr) release();

	//DC 가져오기(현재 윈도우에 대한 화면DC를 임시로 받아옴)
	HDC hdc = GetDC(hWnd);

	//CreateCompatibleDC
	//비트맵을 출력하기 위해서 메모리DC를 만들어 주는 함수
	//화면 DC와 메모리 DC 호환
	//CreateCompatibleBitmap
	//원본 DC와 호환되는 비트맵을 생성해 주는 함수
	//SelectObject
	//기본의 비트맵 핸들을 반환하고, 새로운 비트맵을 메모리 DC가 선택하고
	//메모리 DC에 비트맵이 그려짐, 화면 DC 아니므로 모리터에 출력 x

	//이미지 정보 생성하기
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_FILE;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)LoadImage(hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->x = x - (width / frameX / 2);
	m_imageInfo->y = y - (height / frameY / 2);
	m_imageInfo->width = width;
	m_imageInfo->height = height;
	m_imageInfo->maxFrameX = frameX - 1;
	m_imageInfo->maxFrameY = frameY - 1;
	m_imageInfo->frameWidth = width / frameX;
	m_imageInfo->frameHeight = height / frameY;

	//파일 이름
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);

	//투명키 컬러 셋팅
	m_isTrans = isTrans;
	m_transColor = transColor;

	//알파블렌드 옵션
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.AlphaFormat = 0;	//32비트인경우 AC_SRC_APLHA를 지정하고 그 외에는 0으로 지정함(그렇지 않으면 알파블렌딩을 함수 사용 불가)
	m_blendFunc.BlendOp = AC_SRC_OVER;

	//알파블렌드를 사용하기 위한 이미지 초기화
	m_blendImage = new IMAGE_INFO;
	m_blendImage->loadType = LOAD_FILE;
	m_blendImage->resID = 0;
	m_blendImage->hMemDC = CreateCompatibleDC(hdc);
	m_blendImage->hBit = (HBITMAP)LoadImage(hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_blendImage->hOBit = (HBITMAP)SelectObject(m_blendImage->hMemDC, m_blendImage->hBit);
	m_blendImage->width = WINSIZEX;
	m_blendImage->height = WINSIZEY;

	//리소스를 얻어오는데 실패 했을때
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC 해제
	ReleaseDC(hWnd, hdc);

	return S_OK;
}

void image::setTransColor(bool isTrans, COLORREF transColor)
{
	m_isTrans = isTrans;
	m_transColor = transColor;
}

void image::release()
{
	//이미지 정보가 남아 있다면 릴리즈 해줄 것!!
	if (m_imageInfo)
	{
		SelectObject(m_imageInfo->hMemDC, m_imageInfo->hOBit);
		DeleteObject(m_imageInfo->hOBit);
		DeleteDC(m_imageInfo->hMemDC);

		SelectObject(m_blendImage->hMemDC, m_blendImage->hOBit);
		DeleteObject(m_blendImage->hOBit);
		DeleteDC(m_blendImage->hMemDC);

		SAFE_DELETE(m_imageInfo);
		SAFE_DELETE(m_fileName);
		SAFE_DELETE(m_blendImage);

		m_isTrans = false;
		m_transColor = RGB(0, 0, 0);
	}
}

void image::render(HDC hdc)
{
	//배경색 없앨거냐?
	if (m_isTrans)
	{
		//GdiTransparentBlt : 비트맵을 불러올 때 특정색상 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,					//복사될 장소의 DC
			0,						//복사될 좌표의 시작점x
			0,						//복사될 좌표의 시작점y
			m_imageInfo->width,		//복사될 이미지 가로크기
			m_imageInfo->height,	//복사될 이미지 세로크기
			m_imageInfo->hMemDC,	//복사될 대상 DC
			0,						//복사 시작지점x
			0,						//복사 시작지점y
			m_imageInfo->width,		//복사 영역 가로크기
			m_imageInfo->height,	//복사 영역 세로크기
			m_transColor);			//복사할때 제외할 색상(마젠타)
	}
	//원본 이미지 그대로 출력할거냐?
	else
	{
		//SRCCOPY : 복사해주는 함수 가로 세로를 재정의해서 복사
		//DC간의 영역끼리 고속복사 해주는 함수
		BitBlt(hdc, 0, 0, m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	//배경색 없앨거냐?
	if (m_isTrans)
	{
		//GdiTransparentBlt : 비트맵을 불러올 때 특정색상 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,					//복사될 장소의 DC
			destX,					//복사될 좌표의 시작점x
			destY,					//복사될 좌표의 시작점y
			m_imageInfo->width,		//복사될 이미지 가로크기
			m_imageInfo->height,	//복사될 이미지 세로크기
			m_imageInfo->hMemDC,	//복사될 대상 DC
			0,						//복사 시작지점x
			0,						//복사 시작지점y
			m_imageInfo->width,		//복사 영역 가로크기
			m_imageInfo->height,	//복사 영역 세로크기
			m_transColor);			//복사할때 제외할 색상(마젠타)
	}
	//원본 이미지 그대로 출력할거냐?
	else
	{
		//SRCCOPY : 복사해주는 함수 가로 세로를 재정의해서 복사
		//DC간의 영역끼리 고속복사 해주는 함수
		BitBlt(hdc, destX, destY, m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//배경색 없앨거냐?
	if (m_isTrans)
	{
		//GdiTransparentBlt : 비트맵을 불러올 때 특정색상 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,					//복사될 장소의 DC
			destX,					//복사될 좌표의 시작점x
			destY,					//복사될 좌표의 시작점y
			sourWidth,				//복사될 이미지 가로크기
			sourHeight,				//복사될 이미지 세로크기
			m_imageInfo->hMemDC,	//복사될 대상 DC
			sourX,					//복사 시작지점x
			sourY,					//복사 시작지점y
			sourWidth,				//복사 영역 가로크기
			sourHeight,				//복사 영역 세로크기
			m_transColor);			//복사할때 제외할 색상(마젠타)
	}
	//원본 이미지 그대로 출력할거냐?
	else
	{
		//SRCCOPY : 복사해주는 함수 가로 세로를 재정의해서 복사
		//DC간의 영역끼리 고속복사 해주는 함수
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			m_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//알파값 초기화
	m_blendFunc.SourceConstantAlpha = alpha;

	//배경색(마젠타) 없앤 후 알파블렌딩 할거냐?
	if (m_isTrans)
	{
		//1. 출력해야 될 DC에 그려져 있는 내용을 블렌드 이미지에 그려준다.
		BitBlt(m_blendImage->hMemDC, 0, 0, m_blendImage->width, m_blendImage->height, hdc,
			WINSIZEX, WINSIZEY, SRCCOPY);
		//2. 출력해야 될 이미지를 블렌드에 그려준다(마젠타를 없애준다)
		GdiTransparentBlt(m_blendImage->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height, m_transColor);
		//3. 블렌드 DC를 출력해야 할 DC에 그린다.
		AlphaBlend(hdc, 0, 0, m_imageInfo->width, m_imageInfo->height, m_blendImage->hMemDC,
			0, 0, m_imageInfo->width, m_imageInfo->height, m_blendFunc);
	}
	//원본 이미지 그대로 알파블렌딩 할거냐?
	else
	{
		AlphaBlend(hdc, 0, 0, m_imageInfo->width, m_imageInfo->height, m_imageInfo->hMemDC,
			0, 0, m_imageInfo->width, m_imageInfo->height, m_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//알파값 초기화
	m_blendFunc.SourceConstantAlpha = alpha;

	//배경색(마젠타) 없앤 후 알파블렌딩 할거냐?
	if (m_isTrans)
	{
		//1. 출력해야 될 DC에 그려져 있는 내용을 블렌드 이미지에 그려준다.
		BitBlt(m_blendImage->hMemDC, 0, 0, m_blendImage->width, m_blendImage->height, hdc,
			destX, destY, SRCCOPY);
		//2. 출력해야 될 이미지를 블렌드에 그려준다(마젠타를 없애준다)
		GdiTransparentBlt(m_blendImage->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height, m_transColor);
		//3. 블렌드 DC를 출력해야 할 DC에 그린다.
		AlphaBlend(hdc, destX, destY, m_imageInfo->width, m_imageInfo->height, m_imageInfo->hMemDC,
			0, 0, m_imageInfo->width, m_imageInfo->height, m_blendFunc);
	}
	//원본 이미지 그대로 알파블렌딩 할거냐?
	else
	{
		AlphaBlend(hdc, destX, destY, m_imageInfo->width, m_imageInfo->height, m_imageInfo->hMemDC,
			0, 0, m_imageInfo->width, m_imageInfo->height, m_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//알파값 초기화
	m_blendFunc.SourceConstantAlpha = alpha;

	//배경색(마젠타) 없앤 후 알파블렌딩 할거냐?
	if (m_isTrans)
	{
		//1. 출력해야 될 DC에 그려져 있는 내용을 블렌드 이미지에 그려준다.
		BitBlt(m_blendImage->hMemDC, 0, 0, m_blendImage->width, m_blendImage->height, hdc,
			destX, destY, SRCCOPY);
		//2. 출력해야 될 이미지를 블렌드에 그려준다(마젠타를 없애준다)
		GdiTransparentBlt(m_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			m_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, m_transColor);
		//3. 블렌드 DC를 출력해야 할 DC에 그린다.
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, m_blendImage->hMemDC,
			sourX, sourY, sourWidth, sourHeight, m_blendFunc);
	}
	//원본 이미지 그대로 알파블렌딩 할거냐?
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, m_imageInfo->hMemDC,
			sourX, sourY, sourWidth, sourHeight, m_blendFunc);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	//배경색 없앨거냐?
	if (m_isTrans)
	{
		//GdiTransparentBlt : 비트맵을 불러올 때 특정색상 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,					//복사될 장소의 DC
			destX,					//복사될 좌표의 시작점x
			destY,					//복사될 좌표의 시작점y
			m_imageInfo->frameWidth,				//복사될 이미지 가로크기
			m_imageInfo->frameHeight,				//복사될 이미지 세로크기
			m_imageInfo->hMemDC,	//복사될 대상 DC
			m_imageInfo->currentFrameX * m_imageInfo->frameWidth,					//복사 시작지점x
			m_imageInfo->currentFrameY * m_imageInfo->frameHeight,					//복사 시작지점y
			m_imageInfo->frameWidth,				//복사 영역 가로크기
			m_imageInfo->frameHeight,				//복사 영역 세로크기
			m_transColor);			//복사할때 제외할 색상(마젠타)
	}
	//원본 이미지 그대로 출력할거냐?
	else
	{
		//SRCCOPY : 복사해주는 함수 가로 세로를 재정의해서 복사
		//DC간의 영역끼리 고속복사 해주는 함수
		BitBlt(hdc, destX, destY, m_imageInfo->frameWidth, m_imageInfo->frameHeight,
			m_imageInfo->hMemDC, m_imageInfo->currentFrameX * m_imageInfo->frameWidth, m_imageInfo->currentFrameY * m_imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	m_imageInfo->currentFrameX = currentFrameX;
	m_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > m_imageInfo->maxFrameX)
	{
		m_imageInfo->currentFrameX = m_imageInfo->maxFrameX;
	}

	if (currentFrameY > m_imageInfo->maxFrameY)
	{
		m_imageInfo->currentFrameY = m_imageInfo->maxFrameY;
	}

	//배경색 없앨거냐?
	if (m_isTrans)
	{
		//GdiTransparentBlt : 비트맵을 불러올 때 특정색상 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,					//복사될 장소의 DC
			destX,					//복사될 좌표의 시작점x
			destY,					//복사될 좌표의 시작점y
			m_imageInfo->frameWidth,				//복사될 이미지 가로크기
			m_imageInfo->frameHeight,				//복사될 이미지 세로크기
			m_imageInfo->hMemDC,	//복사될 대상 DC
			currentFrameX * m_imageInfo->frameWidth,					//복사 시작지점x
			currentFrameY * m_imageInfo->frameHeight,					//복사 시작지점y
			m_imageInfo->frameWidth,				//복사 영역 가로크기
			m_imageInfo->frameHeight,				//복사 영역 세로크기
			m_transColor);			//복사할때 제외할 색상(마젠타)
	}
	//원본 이미지 그대로 출력할거냐?
	else
	{
		//SRCCOPY : 복사해주는 함수 가로 세로를 재정의해서 복사
		//DC간의 영역끼리 고속복사 해주는 함수
		BitBlt(hdc, destX, destY, m_imageInfo->frameWidth, m_imageInfo->frameHeight,
			m_imageInfo->hMemDC, currentFrameX * m_imageInfo->frameWidth, currentFrameY * m_imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	m_imageInfo->currentFrameX = currentFrameX;
	m_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > m_imageInfo->maxFrameX)
	{
		m_imageInfo->currentFrameX = m_imageInfo->maxFrameX;
	}

	if (currentFrameY > m_imageInfo->maxFrameY)
	{
		m_imageInfo->currentFrameY = m_imageInfo->maxFrameY;
	}

	alphaRender(hdc, destX, destY, currentFrameX * m_imageInfo->frameWidth, currentFrameY * m_imageInfo->frameWidth, m_imageInfo->frameWidth, m_imageInfo->frameHeight, alpha);
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//sour 이미지, dest DC영역

	//offset 값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = m_imageInfo->width + (offsetX % m_imageInfo->width);
	if (offsetY < 0) offsetY = m_imageInfo->height + (offsetY % m_imageInfo->height);

	//그려지는 소스의 영역(이미지)를 셋팅할 변수
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역
	RECT rcDest;
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프 영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % m_imageInfo->height;
		rcSour.bottom = m_imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어갔다면 (화면 밖으로 나갔을떄)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀의 값을 올려준다.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프 영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 가로계산
			rcSour.left = (x + offsetX) % m_imageInfo->width;
			rcSour.right = m_imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어가면
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 양만큼 라이트값을 왼쪽으로
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top);
		}
	}
}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//sour 이미지, dest DC영역

	//offset 값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = m_imageInfo->width + (offsetX % m_imageInfo->width);
	if (offsetY < 0) offsetY = m_imageInfo->height + (offsetY % m_imageInfo->height);

	//그려지는 소스의 영역(이미지)를 셋팅할 변수
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역
	RECT rcDest;
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프 영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % m_imageInfo->height;
		rcSour.bottom = m_imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어갔다면 (화면 밖으로 나갔을떄)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀의 값을 올려준다.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프 영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 가로계산
			rcSour.left = (x + offsetX) % m_imageInfo->width;
			rcSour.right = m_imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어가면
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 양만큼 라이트값을 왼쪽으로
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자
	
			alphaRender(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top, alpha);
		}
	}
}

void image::aniRender(HDC hdc, int destX, int destY, animation * ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

void image::aniAlphaRender(HDC hdc, int destX, int destY, animation *ani, BYTE alpha)
{
	alphaRender(hdc,destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(),alpha);
}
