#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init(POINT position)
{
	return S_OK;
}

void item::release()
{
}

void item::update()
{
}

void item::render(POINT pt)
{
}



//아모 0
ammo0::ammo0()
{
}

ammo0::~ammo0()
{
}

HRESULT ammo0::init(POINT position)
{
	m_im= IMAGEMANAGER->findImage("아모0") ;
	m_x= position.x;
	m_y= startY=position.y;
	real_rc=RectMakeCenter(m_x, m_y, m_im->getWidth(), m_im->getHeight());
	detect_rc = RectMakeCenter(m_x, m_y, 200, 200);
	speed= 10;
	speedX = RND->getFloatFromInto(-2.0f, 2.0f);
	isDetect=false;
	m_type= AMMO0;
	born = true;
	pick = false;
	return S_OK;
}

void ammo0::release()
{
}

void ammo0::update()
{
	if (m_y < startY + 10&& born)
	{
		m_y -= speed;
		speed -= 0.5f;
		m_x += speedX;
	}
	else
	{
		born = false;
	}
	real_rc = RectMakeCenter(m_x, m_y, m_im->getWidth(), m_im->getHeight());
	detect_rc = RectMakeCenter(m_x, m_y, 200, 200);
}

void ammo0::render(POINT pt)
{
	m_im->render(getMemDC(), real_rc.left - pt.x, real_rc.top - pt.y);
}





ammo1::ammo1()
{
}

ammo1::~ammo1()
{
}

HRESULT ammo1::init(POINT position)
{
	m_im = IMAGEMANAGER->findImage("아모1");
	m_x = position.x;
	m_y = startY= position.y;
	real_rc = RectMakeCenter(m_x, m_y, m_im->getWidth(), m_im->getHeight());
	detect_rc = RectMakeCenter(m_x, m_y, 200, 200);
	speed = 10;
	speedX = RND->getFloatFromInto(-2.0f, 2.0f);
	isDetect = false;
	m_type = AMMO1;
	born = true;
	pick = false;
	return S_OK;
}

void ammo1::release()
{
}

void ammo1::update()
{

	if (m_y < startY + 10 && born)
	{
		m_y -= speed;
		speed -= 0.5f;
		m_x += speedX;
	}
	else
	{
		born = false;
	}
	real_rc = RectMakeCenter(m_x, m_y, m_im->getWidth(), m_im->getHeight());
	detect_rc = RectMakeCenter(m_x, m_y, 200, 200);
}

void ammo1::render(POINT pt)
{
	
	m_im->render(getMemDC(), real_rc.left-pt.x, real_rc.top -pt.y);
}

ammo2::ammo2()
{
}

ammo2::~ammo2()
{
}




HRESULT ammo2::init(POINT position)
{
	m_im = IMAGEMANAGER->findImage("아모2");
	m_x =startX= position.x;
	m_y =startY= position.y;
	real_rc = RectMakeCenter(m_x, m_y, m_im->getWidth(), m_im->getHeight());
	detect_rc = RectMakeCenter(m_x, m_y, 200, 200);
	speed = 10;
	speedX = RND->getFloatFromInto(-2.0f, 2.0f);
	isDetect = false;
	m_type = AMMO2;
	born = true;
	pick = false;
	return S_OK;
}

void ammo2::release()
{
}

void ammo2::update()
{
	if (m_y < startY + 10 && born)
	{
		m_y -= speed;
		speed -= 0.5f;
		m_x += speedX;
	}
	else
	{
		born = false;
	}
	real_rc = RectMakeCenter(m_x, m_y, m_im->getWidth(), m_im->getHeight());
	detect_rc = RectMakeCenter(m_x, m_y, 200, 200);
}

void ammo2::render(POINT pt)
{
	m_im->render(getMemDC(), real_rc.left - pt.x, real_rc.top - pt.y);
}



health::health()
{
}

health::~health()
{
}

HRESULT health::init(POINT position)
{
	m_im = IMAGEMANAGER->findImage("체력");
	m_x = position.x;
	m_y = startY= position.y;
	real_rc = RectMakeCenter(m_x, m_y, m_im->getWidth(), m_im->getHeight());
	detect_rc = RectMakeCenter(m_x, m_y, 200, 200);
	speed = 10;
	speedX = RND->getFloatFromInto(-2.0f, 2.0f);
	isDetect = false;
	m_type = AMMO0;
	born = true;
	pick = false;
	return S_OK;
}

void health::release()
{
}

void health::update()
{
	if (m_y < startY + 10 && born)
	{
		m_y -= speed;
		speed -= 0.5f;
		m_x += speedX;
	}
	else
	{
		born = false;
	}
	real_rc = RectMakeCenter(m_x, m_y, m_im->getWidth(), m_im->getHeight());
	detect_rc = RectMakeCenter(m_x, m_y, 200, 200);
}

void health::render(POINT pt)
{
	m_im->render(getMemDC(), real_rc.left - pt.x, real_rc.top - pt.y);
}
