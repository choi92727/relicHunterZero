#include "stdafx.h"
#include "image.h"
#pragma comment(lib,"msimg32.lib")	//�������带 ����ϱ����ؼ� ���̺귯�� �߰�

/*
���� ) �̹��� ���� ����
1. BMP
������ ������ ���ս� �������̹Ƿ� �ӵ��� ���� ������.

2. JPG
�ս� �����̹Ƿ� ���� ���� �̹����� �ս��� �Ͼ�� ���
��� �˰��� ���� ������ �Ǿ� �뷮�� �۴�.

3. PNG
1,2 ���� �޸� alpha(������) ä���� ����.
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
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �մٸ� ������ ���� ���ٰ�
	if (m_imageInfo != nullptr) release();

	//DC ��������(���� �����쿡 ���� ȭ��DC�� �ӽ÷� �޾ƿ�)
	HDC hdc = GetDC(hWnd);

	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���ؼ� �޸�DC�� ����� �ִ� �Լ�
	//ȭ�� DC�� �޸� DC ȣȯ
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� ������ �ִ� �Լ�
	//SelectObject
	//�⺻�� ��Ʈ�� �ڵ��� ��ȯ�ϰ�, ���ο� ��Ʈ���� �޸� DC�� �����ϰ�
	//�޸� DC�� ��Ʈ���� �׷���, ȭ�� DC �ƴϹǷ� ���Ϳ� ��� x

	//�̹��� ���� �����ϱ�
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_EMPTY;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->width = width;
	m_imageInfo->height = height;

	//�����̸�
	m_fileName = nullptr;

	//����Ű �÷� ����
	m_isTrans = false;
	m_transColor = RGB(0, 0, 0);

	//���ĺ��� �ɼ�
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.AlphaFormat = 0;	//32��Ʈ�ΰ�� AC_SRC_APLHA�� �����ϰ� �� �ܿ��� 0���� ������(�׷��� ������ ���ĺ����� �Լ� ��� �Ұ�)
	m_blendFunc.BlendOp = AC_SRC_OVER;

	//���ĺ��带 ����ϱ� ���� �̹��� �ʱ�ȭ
	m_blendImage = new IMAGE_INFO;
	m_blendImage->loadType = LOAD_EMPTY;
	m_blendImage->resID = 0;
	m_blendImage->hMemDC = CreateCompatibleDC(hdc);
	m_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, m_imageInfo->width, m_imageInfo->height);
	m_blendImage->hOBit = (HBITMAP)SelectObject(m_blendImage->hMemDC, m_blendImage->hBit);
	m_blendImage->width = WINSIZEX;
	m_blendImage->height = WINSIZEY;


	//���ҽ��� �����µ� ���� ������
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const DWORD resID, int width, int height, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �մٸ� ������ ���� ���ٰ�
	if (m_imageInfo != nullptr) release();

	//DC ��������(���� �����쿡 ���� ȭ��DC�� �ӽ÷� �޾ƿ�)
	HDC hdc = GetDC(hWnd);

	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���ؼ� �޸�DC�� ����� �ִ� �Լ�
	//ȭ�� DC�� �޸� DC ȣȯ
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� ������ �ִ� �Լ�
	//SelectObject
	//�⺻�� ��Ʈ�� �ڵ��� ��ȯ�ϰ�, ���ο� ��Ʈ���� �޸� DC�� �����ϰ�
	//�޸� DC�� ��Ʈ���� �׷���, ȭ�� DC �ƴϹǷ� ���Ϳ� ��� x

	//�̹��� ���� �����ϱ�
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_RESOURCE;
	m_imageInfo->resID = resID;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)LoadBitmap(hInstance, MAKEINTRESOURCE(m_imageInfo->resID));//������ ��Ʈ�ʿ� �ø���.
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->width = width;
	m_imageInfo->height = height;

	//�����̸�
	m_fileName = nullptr;

	//����Ű �÷� ����
	m_isTrans = isTrans;
	m_transColor = transColor;

	//���ҽ��� �����µ� ���� ������
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �մٸ� ������ ���� ���ٰ�
	if (m_imageInfo != nullptr) release();

	//DC ��������(���� �����쿡 ���� ȭ��DC�� �ӽ÷� �޾ƿ�)
	HDC hdc = GetDC(hWnd);

	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���ؼ� �޸�DC�� ����� �ִ� �Լ�
	//ȭ�� DC�� �޸� DC ȣȯ
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� ������ �ִ� �Լ�
	//SelectObject
	//�⺻�� ��Ʈ�� �ڵ��� ��ȯ�ϰ�, ���ο� ��Ʈ���� �޸� DC�� �����ϰ�
	//�޸� DC�� ��Ʈ���� �׷���, ȭ�� DC �ƴϹǷ� ���Ϳ� ��� x

	//�̹��� ���� �����ϱ�
	m_imageInfo = new IMAGE_INFO;
	m_imageInfo->loadType = LOAD_FILE;
	m_imageInfo->resID = 0;
	m_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	m_imageInfo->hBit = (HBITMAP)LoadImage(hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_imageInfo->hOBit = (HBITMAP)SelectObject(m_imageInfo->hMemDC, m_imageInfo->hBit);
	m_imageInfo->width = width;
	m_imageInfo->height = height;

	//���� �̸�
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);

	//����Ű �÷� ����
	m_isTrans = isTrans;
	m_transColor = transColor;

	//���ĺ��� �ɼ�
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.AlphaFormat = 0;	//32��Ʈ�ΰ�� AC_SRC_APLHA�� �����ϰ� �� �ܿ��� 0���� ������(�׷��� ������ ���ĺ����� �Լ� ��� �Ұ�)
	m_blendFunc.BlendOp = AC_SRC_OVER;

	//���ĺ��带 ����ϱ� ���� �̹��� �ʱ�ȭ
	m_blendImage = new IMAGE_INFO;
	m_blendImage->loadType = LOAD_FILE;
	m_blendImage->resID = 0;
	m_blendImage->hMemDC = CreateCompatibleDC(hdc);
	m_blendImage->hBit = (HBITMAP)LoadImage(hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_blendImage->hOBit = (HBITMAP)SelectObject(m_blendImage->hMemDC, m_blendImage->hBit);
	m_blendImage->width = WINSIZEX;
	m_blendImage->height = WINSIZEY;

	//���ҽ��� �����µ� ���� ������
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �մٸ� ������ ���� ���ٰ�
	if (m_imageInfo != nullptr) release();

	//DC ��������(���� �����쿡 ���� ȭ��DC�� �ӽ÷� �޾ƿ�)
	HDC hdc = GetDC(hWnd);

	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���ؼ� �޸�DC�� ����� �ִ� �Լ�
	//ȭ�� DC�� �޸� DC ȣȯ
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� ������ �ִ� �Լ�
	//SelectObject
	//�⺻�� ��Ʈ�� �ڵ��� ��ȯ�ϰ�, ���ο� ��Ʈ���� �޸� DC�� �����ϰ�
	//�޸� DC�� ��Ʈ���� �׷���, ȭ�� DC �ƴϹǷ� ���Ϳ� ��� x

	//�̹��� ���� �����ϱ�
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

	//���� �̸�
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);

	//����Ű �÷� ����
	m_isTrans = isTrans;
	m_transColor = transColor;

	//���ĺ��� �ɼ�
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.AlphaFormat = 0;	//32��Ʈ�ΰ�� AC_SRC_APLHA�� �����ϰ� �� �ܿ��� 0���� ������(�׷��� ������ ���ĺ����� �Լ� ��� �Ұ�)
	m_blendFunc.BlendOp = AC_SRC_OVER;

	//���ĺ��带 ����ϱ� ���� �̹��� �ʱ�ȭ
	m_blendImage = new IMAGE_INFO;
	m_blendImage->loadType = LOAD_FILE;
	m_blendImage->resID = 0;
	m_blendImage->hMemDC = CreateCompatibleDC(hdc);
	m_blendImage->hBit = (HBITMAP)LoadImage(hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_blendImage->hOBit = (HBITMAP)SelectObject(m_blendImage->hMemDC, m_blendImage->hBit);
	m_blendImage->width = WINSIZEX;
	m_blendImage->height = WINSIZEY;

	//���ҽ��� �����µ� ���� ������
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �մٸ� ������ ���� ���ٰ�
	if (m_imageInfo != nullptr) release();

	//DC ��������(���� �����쿡 ���� ȭ��DC�� �ӽ÷� �޾ƿ�)
	HDC hdc = GetDC(hWnd);

	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���ؼ� �޸�DC�� ����� �ִ� �Լ�
	//ȭ�� DC�� �޸� DC ȣȯ
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� ������ �ִ� �Լ�
	//SelectObject
	//�⺻�� ��Ʈ�� �ڵ��� ��ȯ�ϰ�, ���ο� ��Ʈ���� �޸� DC�� �����ϰ�
	//�޸� DC�� ��Ʈ���� �׷���, ȭ�� DC �ƴϹǷ� ���Ϳ� ��� x

	//�̹��� ���� �����ϱ�
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

	//���� �̸�
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);

	//����Ű �÷� ����
	m_isTrans = isTrans;
	m_transColor = transColor;

	//���ĺ��� �ɼ�
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.AlphaFormat = 0;	//32��Ʈ�ΰ�� AC_SRC_APLHA�� �����ϰ� �� �ܿ��� 0���� ������(�׷��� ������ ���ĺ����� �Լ� ��� �Ұ�)
	m_blendFunc.BlendOp = AC_SRC_OVER;

	//���ĺ��带 ����ϱ� ���� �̹��� �ʱ�ȭ
	m_blendImage = new IMAGE_INFO;
	m_blendImage->loadType = LOAD_FILE;
	m_blendImage->resID = 0;
	m_blendImage->hMemDC = CreateCompatibleDC(hdc);
	m_blendImage->hBit = (HBITMAP)LoadImage(hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_blendImage->hOBit = (HBITMAP)SelectObject(m_blendImage->hMemDC, m_blendImage->hBit);
	m_blendImage->width = WINSIZEX;
	m_blendImage->height = WINSIZEY;

	//���ҽ��� �����µ� ���� ������
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �մٸ� ������ ���� ���ٰ�
	if (m_imageInfo != nullptr) release();

	//DC ��������(���� �����쿡 ���� ȭ��DC�� �ӽ÷� �޾ƿ�)
	HDC hdc = GetDC(hWnd);

	//CreateCompatibleDC
	//��Ʈ���� ����ϱ� ���ؼ� �޸�DC�� ����� �ִ� �Լ�
	//ȭ�� DC�� �޸� DC ȣȯ
	//CreateCompatibleBitmap
	//���� DC�� ȣȯ�Ǵ� ��Ʈ���� ������ �ִ� �Լ�
	//SelectObject
	//�⺻�� ��Ʈ�� �ڵ��� ��ȯ�ϰ�, ���ο� ��Ʈ���� �޸� DC�� �����ϰ�
	//�޸� DC�� ��Ʈ���� �׷���, ȭ�� DC �ƴϹǷ� ���Ϳ� ��� x

	//�̹��� ���� �����ϱ�
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

	//���� �̸�
	int len = strlen(fileName);
	m_fileName = new char[len + 1];
	strcpy_s(m_fileName, len + 1, fileName);

	//����Ű �÷� ����
	m_isTrans = isTrans;
	m_transColor = transColor;

	//���ĺ��� �ɼ�
	m_blendFunc.BlendFlags = 0;
	m_blendFunc.AlphaFormat = 0;	//32��Ʈ�ΰ�� AC_SRC_APLHA�� �����ϰ� �� �ܿ��� 0���� ������(�׷��� ������ ���ĺ����� �Լ� ��� �Ұ�)
	m_blendFunc.BlendOp = AC_SRC_OVER;

	//���ĺ��带 ����ϱ� ���� �̹��� �ʱ�ȭ
	m_blendImage = new IMAGE_INFO;
	m_blendImage->loadType = LOAD_FILE;
	m_blendImage->resID = 0;
	m_blendImage->hMemDC = CreateCompatibleDC(hdc);
	m_blendImage->hBit = (HBITMAP)LoadImage(hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	m_blendImage->hOBit = (HBITMAP)SelectObject(m_blendImage->hMemDC, m_blendImage->hBit);
	m_blendImage->width = WINSIZEX;
	m_blendImage->height = WINSIZEY;

	//���ҽ��� �����µ� ���� ������
	if (m_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
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
	//�̹��� ������ ���� �ִٸ� ������ ���� ��!!
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
	//���� ���ٰų�?
	if (m_isTrans)
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��� �� Ư������ �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� ����� DC
			0,						//����� ��ǥ�� ������x
			0,						//����� ��ǥ�� ������y
			m_imageInfo->width,		//����� �̹��� ����ũ��
			m_imageInfo->height,	//����� �̹��� ����ũ��
			m_imageInfo->hMemDC,	//����� ��� DC
			0,						//���� ��������x
			0,						//���� ��������y
			m_imageInfo->width,		//���� ���� ����ũ��
			m_imageInfo->height,	//���� ���� ����ũ��
			m_transColor);			//�����Ҷ� ������ ����(����Ÿ)
	}
	//���� �̹��� �״�� ����Ұų�?
	else
	{
		//SRCCOPY : �������ִ� �Լ� ���� ���θ� �������ؼ� ����
		//DC���� �������� ��Ӻ��� ���ִ� �Լ�
		BitBlt(hdc, 0, 0, m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	//���� ���ٰų�?
	if (m_isTrans)
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��� �� Ư������ �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� ����� DC
			destX,					//����� ��ǥ�� ������x
			destY,					//����� ��ǥ�� ������y
			m_imageInfo->width,		//����� �̹��� ����ũ��
			m_imageInfo->height,	//����� �̹��� ����ũ��
			m_imageInfo->hMemDC,	//����� ��� DC
			0,						//���� ��������x
			0,						//���� ��������y
			m_imageInfo->width,		//���� ���� ����ũ��
			m_imageInfo->height,	//���� ���� ����ũ��
			m_transColor);			//�����Ҷ� ������ ����(����Ÿ)
	}
	//���� �̹��� �״�� ����Ұų�?
	else
	{
		//SRCCOPY : �������ִ� �Լ� ���� ���θ� �������ؼ� ����
		//DC���� �������� ��Ӻ��� ���ִ� �Լ�
		BitBlt(hdc, destX, destY, m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//���� ���ٰų�?
	if (m_isTrans)
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��� �� Ư������ �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� ����� DC
			destX,					//����� ��ǥ�� ������x
			destY,					//����� ��ǥ�� ������y
			sourWidth,				//����� �̹��� ����ũ��
			sourHeight,				//����� �̹��� ����ũ��
			m_imageInfo->hMemDC,	//����� ��� DC
			sourX,					//���� ��������x
			sourY,					//���� ��������y
			sourWidth,				//���� ���� ����ũ��
			sourHeight,				//���� ���� ����ũ��
			m_transColor);			//�����Ҷ� ������ ����(����Ÿ)
	}
	//���� �̹��� �״�� ����Ұų�?
	else
	{
		//SRCCOPY : �������ִ� �Լ� ���� ���θ� �������ؼ� ����
		//DC���� �������� ��Ӻ��� ���ִ� �Լ�
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			m_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//���İ� �ʱ�ȭ
	m_blendFunc.SourceConstantAlpha = alpha;

	//����(����Ÿ) ���� �� ���ĺ��� �Ұų�?
	if (m_isTrans)
	{
		//1. ����ؾ� �� DC�� �׷��� �ִ� ������ ���� �̹����� �׷��ش�.
		BitBlt(m_blendImage->hMemDC, 0, 0, m_blendImage->width, m_blendImage->height, hdc,
			WINSIZEX, WINSIZEY, SRCCOPY);
		//2. ����ؾ� �� �̹����� ���忡 �׷��ش�(����Ÿ�� �����ش�)
		GdiTransparentBlt(m_blendImage->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height, m_transColor);
		//3. ���� DC�� ����ؾ� �� DC�� �׸���.
		AlphaBlend(hdc, 0, 0, m_imageInfo->width, m_imageInfo->height, m_blendImage->hMemDC,
			0, 0, m_imageInfo->width, m_imageInfo->height, m_blendFunc);
	}
	//���� �̹��� �״�� ���ĺ��� �Ұų�?
	else
	{
		AlphaBlend(hdc, 0, 0, m_imageInfo->width, m_imageInfo->height, m_imageInfo->hMemDC,
			0, 0, m_imageInfo->width, m_imageInfo->height, m_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//���İ� �ʱ�ȭ
	m_blendFunc.SourceConstantAlpha = alpha;

	//����(����Ÿ) ���� �� ���ĺ��� �Ұų�?
	if (m_isTrans)
	{
		//1. ����ؾ� �� DC�� �׷��� �ִ� ������ ���� �̹����� �׷��ش�.
		BitBlt(m_blendImage->hMemDC, 0, 0, m_blendImage->width, m_blendImage->height, hdc,
			destX, destY, SRCCOPY);
		//2. ����ؾ� �� �̹����� ���忡 �׷��ش�(����Ÿ�� �����ش�)
		GdiTransparentBlt(m_blendImage->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height,
			m_imageInfo->hMemDC, 0, 0, m_imageInfo->width, m_imageInfo->height, m_transColor);
		//3. ���� DC�� ����ؾ� �� DC�� �׸���.
		AlphaBlend(hdc, destX, destY, m_imageInfo->width, m_imageInfo->height, m_imageInfo->hMemDC,
			0, 0, m_imageInfo->width, m_imageInfo->height, m_blendFunc);
	}
	//���� �̹��� �״�� ���ĺ��� �Ұų�?
	else
	{
		AlphaBlend(hdc, destX, destY, m_imageInfo->width, m_imageInfo->height, m_imageInfo->hMemDC,
			0, 0, m_imageInfo->width, m_imageInfo->height, m_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//���İ� �ʱ�ȭ
	m_blendFunc.SourceConstantAlpha = alpha;

	//����(����Ÿ) ���� �� ���ĺ��� �Ұų�?
	if (m_isTrans)
	{
		//1. ����ؾ� �� DC�� �׷��� �ִ� ������ ���� �̹����� �׷��ش�.
		BitBlt(m_blendImage->hMemDC, 0, 0, m_blendImage->width, m_blendImage->height, hdc,
			destX, destY, SRCCOPY);
		//2. ����ؾ� �� �̹����� ���忡 �׷��ش�(����Ÿ�� �����ش�)
		GdiTransparentBlt(m_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			m_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, m_transColor);
		//3. ���� DC�� ����ؾ� �� DC�� �׸���.
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, m_blendImage->hMemDC,
			sourX, sourY, sourWidth, sourHeight, m_blendFunc);
	}
	//���� �̹��� �״�� ���ĺ��� �Ұų�?
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, m_imageInfo->hMemDC,
			sourX, sourY, sourWidth, sourHeight, m_blendFunc);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	//���� ���ٰų�?
	if (m_isTrans)
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��� �� Ư������ �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� ����� DC
			destX,					//����� ��ǥ�� ������x
			destY,					//����� ��ǥ�� ������y
			m_imageInfo->frameWidth,				//����� �̹��� ����ũ��
			m_imageInfo->frameHeight,				//����� �̹��� ����ũ��
			m_imageInfo->hMemDC,	//����� ��� DC
			m_imageInfo->currentFrameX * m_imageInfo->frameWidth,					//���� ��������x
			m_imageInfo->currentFrameY * m_imageInfo->frameHeight,					//���� ��������y
			m_imageInfo->frameWidth,				//���� ���� ����ũ��
			m_imageInfo->frameHeight,				//���� ���� ����ũ��
			m_transColor);			//�����Ҷ� ������ ����(����Ÿ)
	}
	//���� �̹��� �״�� ����Ұų�?
	else
	{
		//SRCCOPY : �������ִ� �Լ� ���� ���θ� �������ؼ� ����
		//DC���� �������� ��Ӻ��� ���ִ� �Լ�
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

	//���� ���ٰų�?
	if (m_isTrans)
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��� �� Ư������ �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� ����� DC
			destX,					//����� ��ǥ�� ������x
			destY,					//����� ��ǥ�� ������y
			m_imageInfo->frameWidth,				//����� �̹��� ����ũ��
			m_imageInfo->frameHeight,				//����� �̹��� ����ũ��
			m_imageInfo->hMemDC,	//����� ��� DC
			currentFrameX * m_imageInfo->frameWidth,					//���� ��������x
			currentFrameY * m_imageInfo->frameHeight,					//���� ��������y
			m_imageInfo->frameWidth,				//���� ���� ����ũ��
			m_imageInfo->frameHeight,				//���� ���� ����ũ��
			m_transColor);			//�����Ҷ� ������ ����(����Ÿ)
	}
	//���� �̹��� �״�� ����Ұų�?
	else
	{
		//SRCCOPY : �������ִ� �Լ� ���� ���θ� �������ؼ� ����
		//DC���� �������� ��Ӻ��� ���ִ� �Լ�
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
	//sour �̹���, dest DC����

	//offset ���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = m_imageInfo->width + (offsetX % m_imageInfo->width);
	if (offsetY < 0) offsetY = m_imageInfo->height + (offsetY % m_imageInfo->height);

	//�׷����� �ҽ��� ����(�̹���)�� ������ ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ����
	RECT rcDest;
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ���� ����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % m_imageInfo->height;
		rcSour.bottom = m_imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ� (ȭ�� ������ ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ������ ���� �÷��ش�.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ���� ����
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���ΰ��
			rcSour.left = (x + offsetX) % m_imageInfo->width;
			rcSour.right = m_imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ��
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �縸ŭ ����Ʈ���� ��������
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, rcSour.right - rcSour.left, rcSour.bottom - rcSour.top);
		}
	}
}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//sour �̹���, dest DC����

	//offset ���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = m_imageInfo->width + (offsetX % m_imageInfo->width);
	if (offsetY < 0) offsetY = m_imageInfo->height + (offsetY % m_imageInfo->height);

	//�׷����� �ҽ��� ����(�̹���)�� ������ ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ����
	RECT rcDest;
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ���� ����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % m_imageInfo->height;
		rcSour.bottom = m_imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ� (ȭ�� ������ ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ������ ���� �÷��ش�.
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ���� ����
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���ΰ��
			rcSour.left = (x + offsetX) % m_imageInfo->width;
			rcSour.right = m_imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ��
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �縸ŭ ����Ʈ���� ��������
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����
	
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
