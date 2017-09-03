#include "stdafx.h"
#include "imageManager.h"

imageManager::imageManager()
{
}

imageManager::~imageManager()
{
}

HRESULT imageManager::init()
{
	return S_OK;
}

void imageManager::release()
{
	deleteAll();
}

image * imageManager::addImage(string strKey, int width, int height)
{
	//�߰� �Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ����
	if (img) return img;

	img = new image;
	//�̹����� ����� �ʱ�ȭ ���� �ʾҾƸ� null����
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	//m_mImageList.insert(pair<string, image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//�߰� �Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ����
	if (img) return img;

	img = new image;
	//�̹����� ����� �ʱ�ȭ ���� �ʾҾƸ� null����
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	//m_mImageList.insert(pair<string, image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//�߰� �Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ����
	if (img) return img;

	img = new image;
	//�̹����� ����� �ʱ�ȭ ���� �ʾҾƸ� null����
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	//m_mImageList.insert(pair<string, image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�߰� �Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ����
	if (img) return img;

	img = new image;
	//�̹����� ����� �ʱ�ȭ ���� �ʾҾƸ� null����
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	//m_mImageList.insert(pair<string, image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//�߰� �Ϸ��� Ű������ �̹����� �����ϴ��� Ȯ��
	image* img = findImage(strKey);

	//�߰��Ϸ��� �̹����� �̹� �����Ѵٸ� ���� ������ �ʰ� �̹����� ����
	if (img) return img;

	img = new image;
	//�̹����� ����� �ʱ�ȭ ���� �ʾҾƸ� null����
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//������ �̹����� ������ ���� �̹��� ��Ͽ� �߰��Ѵ�.
	//m_mImageList.insert(pair<string, image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::findImage(string strkey)
{
	//�ش�Ű�� �˻�
	mapImageListIter key = m_mImageList.find(strkey);

	//�˻��� Ű�� ã�Ҵٸ�
	if (key != m_mImageList.end())
	{
		return key->second;
	}

	//�˻��� Ű�� ��ã���� nullptr ����
	return nullptr;
}

bool imageManager::deleteImage(string strKey)
{
	//�ش�Ű�� �˻�
	mapImageListIter key = m_mImageList.find(strKey);

	//�˻��� Ű�� ã�Ҵٸ�
	if (key != m_mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		m_mImageList.erase(key);

		return true;
	}

	return false;
}

bool imageManager::deleteAll()
{
	//�� ��ü�� ���鼭 ������
	mapImageListIter iter = m_mImageList.begin();
	for (iter; iter != m_mImageList.end();)
	{
		if (iter->second != nullptr)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);
			iter = m_mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	m_mImageList.clear();

	return true;
}

void imageManager::render(string strKey, HDC hdc)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentframeX, int currentframeY)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentframeX, currentframeY);
}

void imageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentframeX, int currentframeY, BYTE alpha)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strKey);
	if (img) img->frameAlphaRender(hdc, destX, destY, currentframeX, currentframeY, alpha);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//�̹����� ã�� �� ����
	image* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}






