#pragma once
#include "singletonBase.h"
#include "image.h"
class imageManager : public singletonBase<imageManager>
{
private:
	typedef map<string, image*> mapImageList;	//������ ���� �̹��� ���
	typedef map<string, image*>::iterator mapImageListIter;//������ ���� �̹��� ����� �ݺ���

	mapImageList m_mImageList;	//������ ������ �̹��� ���

public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	//Ű������ �� ��Ʈ�� �ʱ�ȭ
	image* addImage(string strKey, int width, int height);
	//Ű������ �̹��� ���� �ʱ�ȭ(�� ���)
	image* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//Ű������ ������ �̹��� ���Ϸ� �ʱ�ȭ
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	//�̹��� Ű������ ã��
	image* findImage(string strkey);
	//�̹��� Ű������ ����
	bool deleteImage(string strKey);
	//�̹��� ��ü ����
	bool deleteAll();

	//�Ϲݷ���
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//���ķ���
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//�����ӷ���
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentframeX, int currentframeY);
	void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentframeX, int currentframeY, BYTE alpha);

	//��������
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);




};