#include "stdafx.h"
#include "numberDrawManager.h"


numberDrawManager::numberDrawManager()
{
}


numberDrawManager::~numberDrawManager()
{
}

HRESULT numberDrawManager::init(string strKey, int size)
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

void numberDrawManager::update(int x)
{
	if (x / 10000 > 1)
	{
		number[4] = x / 10000;
	}
	else if (x / 1000 > 1)
	{
		number[3] = (x / 1000) % 10;
	}
	else if (x / 100 > 1)
	{
		number[2] = (x / 100) % 10;
	}
	else if (x / 10 > 1)
	{
		number[1] = (x / 10) % 10;
	}
	else
	{
		number[0] = x % 10;
	}
}

void numberDrawManager::render(int left, int top,int spaceSize)
{
	number_image->frameRender(getMemDC(), left, top, number[4], 0);

}
