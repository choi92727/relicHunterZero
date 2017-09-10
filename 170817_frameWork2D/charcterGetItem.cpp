#include "stdafx.h"
#include "charcterGetItem.h"


charcterGetItem::charcterGetItem()
{
}


charcterGetItem::~charcterGetItem()
{
}

HRESULT charcterGetItem::init()
{
	m_im = IMAGEMANAGER->findImage("주울수있다");
	
	int arrLen1[] = {0,1,2,3,4,5,6,7 };
	ANIMATIONMANAGER->addAnimation("줍는거", "주울수있다", arrLen1, 8, 10, false);
	m_ani = ANIMATIONMANAGER->findAnimation("줍는거");
	m_can = false;
	return S_OK;
}

void charcterGetItem::release()
{
}

void charcterGetItem::update(float x, float y)
{
	if (m_can)
	{
		if (!m_ani->isPlay())
		{
			m_ani->start();
		}
	}
	else
	{
		m_ani->stop();
	}
	m_pt = { (int)x+15,(int)y-60 };
}

void charcterGetItem::render(POINT pt)
{
	if(m_can)
	m_im->aniRender(getMemDC(), m_pt.x - pt.x, m_pt.y - pt.y, m_ani);
}
