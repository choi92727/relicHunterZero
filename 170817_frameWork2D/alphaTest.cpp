#include "stdafx.h"
#include "alphaTest.h"


alphaTest::alphaTest()
{
}


alphaTest::~alphaTest()
{
}

HRESULT alphaTest::init()
{
	m_tp = new teleport;
	m_tp->init();
	
	
	return S_OK;
}

void alphaTest::release()
{

}

void alphaTest::update()
{
	m_tp->update();
}

void alphaTest::render()
{
	
	m_tp->render();
}
