#pragma once
#include "animation.h"

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//리소스 로딩
		LOAD_FILE,			//파일 로딩
		LOAD_EMPTY,			//빈 비트맵 파일
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;		//리소스ID
		HDC			hMemDC;		//메모리DC
		HBITMAP		hBit;		//비트맵(새로운 비트맵 핸들)
		HBITMAP		hOBit;		//올드 비트맵(기존 비트맵 핸들)

		float		x;			//이미지 x좌표
		float		y;			//이미지 y좌표

		int			width;		//이미지 가로크기
		int			height;		//이미지 세로크기

		int			currentFrameX;	//현재 프레임 x
		int			currentFrameY;	//현재 프레임 y
		int			maxFrameX;		//최대 x프레임 갯수
		int			maxFrameY;		//최대 y프레임 갯수
		int			frameWidth;		//1프레임 가로길이
		int			frameHeight;	//1프레임 세로길이

		BYTE		loadType;	//로드 타입

		tagImage()
		{
			resID = 0;
			hMemDC = nullptr;
			hBit = nullptr;
			hOBit = nullptr;

			x = 0;
			y = 0;

			width = 0;
			height = 0;

			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;

			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO m_imageInfo;	//이미지 정보
	char*	m_fileName;			//이미지 이름
	bool	m_isTrans;			//배경색 없앨거냐?(마젠타)
	COLORREF	m_transColor;	//배경색 없앨 RGB(마젠타 = RGB(255,0,255))

	BLENDFUNCTION m_blendFunc;	//알파블렌드를 위한 정보
	LPIMAGE_INFO m_blendImage;	//알파블렌드를 사용하기 위한 이미지 정보

public:
	image();
	~image();

	//빈 비트맵 초기화
	HRESULT init(int width, int height);
	//이미지 리소스 초기화(사용안함)
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	//이미지 파일 초기화
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	//프레임 이미지 파일로 초기화
	HRESULT init(const char* fileName, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	//투명키 셋팅
	void setTransColor(bool isTrans, COLORREF transColor);

	//릴리즈
	void release();

	//렌더(내가 지정한 위치에 이미지를 출력)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//알파렌더
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//프레임렌더
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	//루프렌더(hdc, 루프시킬영역, x오프셋, y오프셋)
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//애니메이션 렌더
	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	void aniAlphaRender(HDC hdc, int destX, int destY, animation* ani, BYTE alpha);

	//DC 얻어온다
	inline HDC getMemDC() { return m_imageInfo->hMemDC; }

	//이미지 좌표 x얻기
	inline float getX() { return m_imageInfo->x; }
	inline void setX(float x) { m_imageInfo->x = x; }

	//이미지 좌표 y얻기
	inline float getY() { return m_imageInfo->y; }
	inline void setY(float y) { m_imageInfo->y = y; }

	//이미지 센터좌표 셋팅
	inline void setCenter(float x, float y)
	{
		m_imageInfo->x = x - (m_imageInfo->width / 2);
		m_imageInfo->y = y - (m_imageInfo->height / 2);
	}

	//가로세로 크기 얻기
	inline int getWidth() { return m_imageInfo->width; }
	inline int getHeight() { return m_imageInfo->height; }

	//바운딩 박스(충돌용)
	inline RECT getBoundingBox()
	{
		RECT rc = RectMakeCenter(m_imageInfo->x, m_imageInfo->y, m_imageInfo->width, m_imageInfo->height);
		return rc;
	}

	//프레임 x 셋팅
	inline int getFrameX() { return m_imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		m_imageInfo->currentFrameX = frameX;
		if (frameX > m_imageInfo->maxFrameX)
		{
			m_imageInfo->currentFrameX = m_imageInfo->maxFrameX;
		}
	}

	//프레임 y 셋팅
	inline int getFrameY() { return m_imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		m_imageInfo->currentFrameY = frameY;
		if (frameY > m_imageInfo->maxFrameY)
		{
			m_imageInfo->currentFrameY = m_imageInfo->maxFrameY;
		}
	}

	//1프레임 가로세로 크기
	inline int getFrameWidth() { return m_imageInfo->frameWidth; }
	inline int getFrameHeight() { return m_imageInfo->frameHeight; }

	//맥스프레임 x,y
	inline int getMaxFrameX() { return m_imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return m_imageInfo->maxFrameY; }
};