#include "stdafx.h"
#include "numberDrawManager.h"


numberDrawManager::numberDrawManager()
{
}


numberDrawManager::~numberDrawManager()
{
}

HRESULT numberDrawManager::init(string strKey, int size)//이미지 이름, 자릿수 1~5
{
	number_image = IMAGEMANAGER->findImage(strKey);
	numberSize = size;
	for (int i = 0; i < 5; i++)
	{
		number[i] = 0;
	}
	

	return S_OK;
}

void numberDrawManager::release()
{
}

void numberDrawManager::update(int x)//지금값
{
	if (x < 0)
	{
		x = 0;
	}


	number[4] = x / 10000;

	number[3] = (x / 1000) % 10;

	number[2] = (x / 100) % 10;

	number[1] = (x / 10) % 10;

	number[0] = x % 10;


	
}

void numberDrawManager::render(int left, int top,int spaceSize)//
{
	for (int i = 0; i < numberSize; i++)
	{
		number_image->frameRender(getMemDC(), left+i*(spaceSize+ number_image->getFrameWidth()), top, number[numberSize-i-1], 0);

	}
}
