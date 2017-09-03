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
	//추가 하려는 키값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴
	if (img) return img;

	img = new image;
	//이미지가 제대로 초기화 되지 않았아면 null리턴
	if (FAILED(img->init(width, height)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다.
	//m_mImageList.insert(pair<string, image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//추가 하려는 키값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴
	if (img) return img;

	img = new image;
	//이미지가 제대로 초기화 되지 않았아면 null리턴
	if (FAILED(img->init(fileName, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다.
	//m_mImageList.insert(pair<string, image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//추가 하려는 키값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴
	if (img) return img;

	img = new image;
	//이미지가 제대로 초기화 되지 않았아면 null리턴
	if (FAILED(img->init(fileName, x, y, width, height, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다.
	//m_mImageList.insert(pair<string, image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//추가 하려는 키값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴
	if (img) return img;

	img = new image;
	//이미지가 제대로 초기화 되지 않았아면 null리턴
	if (FAILED(img->init(fileName, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다.
	//m_mImageList.insert(pair<string, image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::addFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//추가 하려는 키값으로 이미지가 존재하는지 확인
	image* img = findImage(strKey);

	//추가하려는 이미지가 이미 존재한다면 새로 만들지 않고 이미지를 리턴
	if (img) return img;

	img = new image;
	//이미지가 제대로 초기화 되지 않았아면 null리턴
	if (FAILED(img->init(fileName, x, y, width, height, frameX, frameY, isTrans, transColor)))
	{
		SAFE_DELETE(img);
		return nullptr;
	}

	//생성된 이미지를 맵으로 만든 이미지 목록에 추가한다.
	//m_mImageList.insert(pair<string, image*>(strKey, img));
	m_mImageList.insert(make_pair(strKey, img));

	return img;
}

image * imageManager::findImage(string strkey)
{
	//해당키를 검색
	mapImageListIter key = m_mImageList.find(strkey);

	//검색한 키를 찾았다면
	if (key != m_mImageList.end())
	{
		return key->second;
	}

	//검색한 키로 못찾으면 nullptr 리턴
	return nullptr;
}

bool imageManager::deleteImage(string strKey)
{
	//해당키를 검색
	mapImageListIter key = m_mImageList.find(strKey);

	//검색한 키를 찾았다면
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
	//맵 전체를 돌면서 지워라
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
	//이미지를 찾은 후 렌더
	image* img = findImage(strKey);
	if (img) img->render(hdc);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾은 후 렌더
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY);
}

void imageManager::render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	//이미지를 찾은 후 렌더
	image* img = findImage(strKey);
	if (img) img->render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha)
{
	//이미지를 찾은 후 렌더
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, alpha);
}

void imageManager::alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//이미지를 찾은 후 렌더
	image* img = findImage(strKey);
	if (img) img->alphaRender(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight, alpha);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY)
{
	//이미지를 찾은 후 렌더
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY);
}

void imageManager::frameRender(string strKey, HDC hdc, int destX, int destY, int currentframeX, int currentframeY)
{
	//이미지를 찾은 후 렌더
	image* img = findImage(strKey);
	if (img) img->frameRender(hdc, destX, destY, currentframeX, currentframeY);
}

void imageManager::frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentframeX, int currentframeY, BYTE alpha)
{
	//이미지를 찾은 후 렌더
	image* img = findImage(strKey);
	if (img) img->frameAlphaRender(hdc, destX, destY, currentframeX, currentframeY, alpha);
}

void imageManager::loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//이미지를 찾은 후 렌더
	image* img = findImage(strKey);
	if (img) img->loopRender(hdc, drawArea, offsetX, offsetY);
}

void imageManager::loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//이미지를 찾은 후 렌더
	image* img = findImage(strKey);
	if (img) img->loopAlphaRender(hdc, drawArea, offsetX, offsetY, alpha);
}






