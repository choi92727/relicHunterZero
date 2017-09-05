#include "stdafx.h"
#include "gunInterface.h"


gunInterface::gunInterface()
{
}


gunInterface::~gunInterface()
{
}

HRESULT gunInterface::init(CHARACTER playerType)
{
	return E_NOTIMPL;
}

void gunInterface::release()
{
}

void gunInterface::update()
{
}

void gunInterface::render()
{
}

void gunInterface::fire()
{
}

void gunInterface::setAngle()
{
}

void gunInterface::setPosition(int x, int y)
{
}

bulletInterface gunInterface::getBullet()
{
	return bulletInterface();
}
