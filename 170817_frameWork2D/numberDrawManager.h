#pragma once
#include "gameNode.h"
class numberDrawManager :
	public gameNode
{
private:
	image* number_image;
	int number[5];
	int numberSize;
public:
	numberDrawManager();
	~numberDrawManager();

	HRESULT init(string strKey, int size);
	void release();
	void update(int x);
	void render(int left, int top, int spaceSize);
};

