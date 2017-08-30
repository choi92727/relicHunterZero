#pragma once
#include "gameNode.h"
#include "progressBar.h"

//로드 아이템 종류
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,		//빈 비트맵 이미지
	LOAD_KIND_IMAGE_1,		//일반 이미지
	LOAD_KIND_IMAGE_2,		//일반 이미지(위치 좌표 있음)
	LOAD_KIND_FRAMEIMAGE_0,	//프레임 이미지
	LOAD_KIND_FRAMEIMAGE_1, //프레임 이미지(위치 값 있음)
	LOAD_KIND_SOUND,
	LOAD_KIND_END
};

//이미지 리소스 구조체
struct tagImageResource
{
	string keyName;			//이미지 키값
	const char* fileName;	//파일 이름
	int x, y;				//위치 좌표
	int width, height;		//가로 세로 크기
	int frameX, frameY;
	bool trans;
	COLORREF transColor;
};

class loadItem
{
private:
	LOAD_KIND m_kind;
	tagImageResource m_imageResource;

public:
	loadItem() {}
	~loadItem() {}

	//키값으로 빈 비트맵 초기화
	HRESULT initForImage(string keyName, int width, int height);
	//키값으로 이미지 파일로 초기화
	HRESULT initForImage(string keyName, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForImage(string keyName, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//키값으로 프레임 이미지 파일로 초기화
	HRESULT initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	//로드 아이템 종류 가져오기
	LOAD_KIND getLoadingKind() { return m_kind; }
	//이미지 리소스 가져오기
	tagImageResource getImageResource() { return m_imageResource; }

};

class loading : public gameNode
{
private:
	typedef vector<loadItem*> arrLoadItem;

	arrLoadItem m_vLoadItem;

	//로딩화면에서 사용할 이미지 및 로딩바
	image* m_backGround;
	progressBar* m_loadingBar;	//로딩 화면에서 사용할 로딩바
	int m_currentGauge;			//로딩바 게이지

public:
	loading() {};
	~loading() {};

	HRESULT init();
	void release();
	void update();
	void render();

	//키 값으로 빈 비트맵 초기화
	void loadImage(string keyName, int width, int height);
	//키 값으로 이미지 파일 초기화
	void loadImage(string keyName, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void loadImage(string keyName, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//키 값으로 프레임 이미지 파일 초기화
	void loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void loadFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	//로딩 완료 됫냐?(로딩 완료 후 씬 변경)
	bool loadingDone();
	//로드 아이템 벡터 가져오기
	vector<loadItem*> getLoadItem() { return m_vLoadItem; }
};

