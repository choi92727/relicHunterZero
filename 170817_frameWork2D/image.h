#pragma once
#include "animation.h"

class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//���ҽ� �ε�
		LOAD_FILE,			//���� �ε�
		LOAD_EMPTY,			//�� ��Ʈ�� ����
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;		//���ҽ�ID
		HDC			hMemDC;		//�޸�DC
		HBITMAP		hBit;		//��Ʈ��(���ο� ��Ʈ�� �ڵ�)
		HBITMAP		hOBit;		//�õ� ��Ʈ��(���� ��Ʈ�� �ڵ�)

		float		x;			//�̹��� x��ǥ
		float		y;			//�̹��� y��ǥ

		int			width;		//�̹��� ����ũ��
		int			height;		//�̹��� ����ũ��

		int			currentFrameX;	//���� ������ x
		int			currentFrameY;	//���� ������ y
		int			maxFrameX;		//�ִ� x������ ����
		int			maxFrameY;		//�ִ� y������ ����
		int			frameWidth;		//1������ ���α���
		int			frameHeight;	//1������ ���α���

		BYTE		loadType;	//�ε� Ÿ��

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
	LPIMAGE_INFO m_imageInfo;	//�̹��� ����
	char*	m_fileName;			//�̹��� �̸�
	bool	m_isTrans;			//���� ���ٰų�?(����Ÿ)
	COLORREF	m_transColor;	//���� ���� RGB(����Ÿ = RGB(255,0,255))

	BLENDFUNCTION m_blendFunc;	//���ĺ��带 ���� ����
	LPIMAGE_INFO m_blendImage;	//���ĺ��带 ����ϱ� ���� �̹��� ����

public:
	image();
	~image();

	//�� ��Ʈ�� �ʱ�ȭ
	HRESULT init(int width, int height);
	//�̹��� ���ҽ� �ʱ�ȭ(������)
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	//�̹��� ���� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	//������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	//����Ű ����
	void setTransColor(bool isTrans, COLORREF transColor);

	//������
	void release();

	//����(���� ������ ��ġ�� �̹����� ���)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//���ķ���
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//�����ӷ���
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	//��������(hdc, ������ų����, x������, y������)
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	//�ִϸ��̼� ����
	void aniRender(HDC hdc, int destX, int destY, animation* ani);
	void aniAlphaRender(HDC hdc, int destX, int destY, animation* ani, BYTE alpha);

	//DC ���´�
	inline HDC getMemDC() { return m_imageInfo->hMemDC; }

	//�̹��� ��ǥ x���
	inline float getX() { return m_imageInfo->x; }
	inline void setX(float x) { m_imageInfo->x = x; }

	//�̹��� ��ǥ y���
	inline float getY() { return m_imageInfo->y; }
	inline void setY(float y) { m_imageInfo->y = y; }

	//�̹��� ������ǥ ����
	inline void setCenter(float x, float y)
	{
		m_imageInfo->x = x - (m_imageInfo->width / 2);
		m_imageInfo->y = y - (m_imageInfo->height / 2);
	}

	//���μ��� ũ�� ���
	inline int getWidth() { return m_imageInfo->width; }
	inline int getHeight() { return m_imageInfo->height; }

	//�ٿ�� �ڽ�(�浹��)
	inline RECT getBoundingBox()
	{
		RECT rc = RectMakeCenter(m_imageInfo->x, m_imageInfo->y, m_imageInfo->width, m_imageInfo->height);
		return rc;
	}

	//������ x ����
	inline int getFrameX() { return m_imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		m_imageInfo->currentFrameX = frameX;
		if (frameX > m_imageInfo->maxFrameX)
		{
			m_imageInfo->currentFrameX = m_imageInfo->maxFrameX;
		}
	}

	//������ y ����
	inline int getFrameY() { return m_imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		m_imageInfo->currentFrameY = frameY;
		if (frameY > m_imageInfo->maxFrameY)
		{
			m_imageInfo->currentFrameY = m_imageInfo->maxFrameY;
		}
	}

	//1������ ���μ��� ũ��
	inline int getFrameWidth() { return m_imageInfo->frameWidth; }
	inline int getFrameHeight() { return m_imageInfo->frameHeight; }

	//�ƽ������� x,y
	inline int getMaxFrameX() { return m_imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return m_imageInfo->maxFrameY; }
};