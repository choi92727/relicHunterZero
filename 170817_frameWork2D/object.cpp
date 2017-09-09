#include "stdafx.h"
#include "object.h"


object::object()
{
}


object::~object()
{
}

HRESULT object::init(POINT position)
{
	return S_OK;
}

void object::release()
{
}

void object::update()
{
}

void object::render(POINT pt)
{
}

void object::animation()
{
}

bool object::dead()
{
	return false;
}

//====================================================================   �ڽ�1
HRESULT box1::init(POINT position)
{
	ZeroMemory(&m_object, sizeof(m_object));

	m_object.image = IMAGEMANAGER->findImage("�ڽ�1");
	m_object.x = position.x;
	m_object.y = position.y;
	m_object.rc = RectMake(m_object.x, m_object.y, 64, 96);
	m_object.hp = 100;
	m_object.count = m_object.currentFrameX = 0;
	m_object.current = ALIVE_OBJECT;
	m_object.isTeleport = false;
	return S_OK;
}

void box1::release()
{
}

void box1::update()
{
	m_object.rc = RectMake(m_object.x, m_object.y, 64, 96);

	animation();
	dead();
}

void box1::render(POINT pt)
{
	Rectangle(getMemDC(), m_object.rc.left - pt.x, m_object.rc.top - pt.y, m_object.rc.right - pt.x, m_object.rc.bottom - pt.y);
	if (m_object.current == ALIVE_OBJECT) m_object.image->frameRender(getMemDC(), m_object.x - 42 - pt.x, m_object.y - 19 - pt.y, m_object.currentFrameX, 0);
	else m_object.image->frameRender(getMemDC(), m_object.x - 84 - pt.x, m_object.y - 22 - pt.y, m_object.currentFrameX, 0);
}

void box1::animation()
{
	if (m_object.current == ALIVE_OBJECT)
	{
		if (67 <= m_object.hp) m_object.currentFrameX = 0;
		else if (34 <= m_object.hp && m_object.hp < 67) m_object.currentFrameX = 1;
		else if (0 < m_object.hp && m_object.hp < 34) m_object.currentFrameX = 2;
		else if (m_object.hp <= 0)
		{
			m_object.image = IMAGEMANAGER->findImage("�ڽ�1 �ı�");
			m_object.currentFrameX = 0;
			m_object.current = DEAD_OBJECT;
		}
	}
}

bool box1::dead()
{
	if (m_object.current == DEAD_OBJECT)
	{
		m_object.count++;
		if (m_object.count % 5 == 0)
		{
			m_object.count = 0;
			m_object.currentFrameX++;
			if (m_object.currentFrameX > IMAGEMANAGER->findImage("�ڽ�1 �ı�")->getMaxFrameX()) return true;
		}
	}
	return false;
}

//====================================================================   �ڽ�2
HRESULT box2::init(POINT position)
{
	ZeroMemory(&m_object, sizeof(m_object));

	m_object.image = IMAGEMANAGER->findImage("�ڽ�2");
	m_object.x = position.x;
	m_object.y = position.y;
	m_object.rc = RectMake(m_object.x, m_object.y, 124, 96);
	m_object.hp = 100;
	m_object.count = m_object.currentFrameX = 0;
	m_object.current = ALIVE_OBJECT;
	m_object.isTeleport = false;
	return S_OK;
}

void box2::release()
{
}

void box2::update()
{
	m_object.rc = RectMake(m_object.x, m_object.y, 124, 96);

	animation();
	dead();
}

void box2::render(POINT pt)
{
	if (m_object.current == ALIVE_OBJECT) m_object.image->frameRender(getMemDC(), m_object.x - 12 - pt.x, m_object.y - 19 - pt.y, m_object.currentFrameX, 0);
	else m_object.image->frameRender(getMemDC(), m_object.x - 54 - pt.x, m_object.y - 22 - pt.y, m_object.currentFrameX, 0);
}

void box2::animation()
{
	if (m_object.current == ALIVE_OBJECT)
	{
		if (67 <= m_object.hp) m_object.currentFrameX = 0;
		else if (34 <= m_object.hp && m_object.hp < 67) m_object.currentFrameX = 1;
		else if (0 < m_object.hp && m_object.hp < 34) m_object.currentFrameX = 2;
		else if (m_object.hp <= 0)
		{
			m_object.image = IMAGEMANAGER->findImage("�ڽ�2 �ı�");
			m_object.currentFrameX = 0;
			m_object.current = DEAD_OBJECT;
		}
	}
}

bool box2::dead()
{
	if (m_object.current == DEAD_OBJECT)
	{
		m_object.count++;
		if (m_object.count % 5 == 0)
		{
			m_object.count = 0;
			m_object.currentFrameX++;
			if (m_object.currentFrameX > IMAGEMANAGER->findImage("�ڽ�2 �ı�")->getMaxFrameX()) return true;
		}
	}
	return false;
}

//====================================================================   ��Ʈ1
HRESULT root1::init(POINT position)
{
	ZeroMemory(&m_object, sizeof(m_object));

	m_object.image = IMAGEMANAGER->findImage("��Ʈ1");
	m_object.x = position.x;
	m_object.y = position.y;
	m_object.rc = RectMake(m_object.x, m_object.y, 160, 70);
	m_object.hp = 100;
	m_object.count = m_object.currentFrameX = 0;
	m_object.current = ALIVE_OBJECT;
	m_object.isTeleport = false;
	return S_OK;
}

void root1::release()
{
}

void root1::update()
{
	m_object.rc = RectMake(m_object.x, m_object.y, 160, 70);

	animation();
	dead();
}

void root1::render(POINT pt)
{
	if (m_object.current == ALIVE_OBJECT) m_object.image->frameRender(getMemDC(), m_object.x - 47 - pt.x, m_object.y - 32 - pt.y, m_object.currentFrameX, 0);
	else  m_object.image->frameRender(getMemDC(), m_object.x - 47 - pt.x, m_object.y - 32 - pt.y, m_object.currentFrameX, 0);
}

void root1::animation()
{
	if (m_object.current == ALIVE_OBJECT)
	{
		if (67 <= m_object.hp) m_object.currentFrameX = 0;
		else if (34 <= m_object.hp && m_object.hp < 67) m_object.currentFrameX = 1;
		else if (0 < m_object.hp && m_object.hp < 34) m_object.currentFrameX = 2;
		else if (m_object.hp <= 0)
		{
			m_object.image = IMAGEMANAGER->findImage("��Ʈ1 �ı�");
			m_object.currentFrameX = 0;
			m_object.current = DEAD_OBJECT;
		}
	}
}

bool root1::dead()
{
	if (m_object.current == DEAD_OBJECT)
	{
		m_object.count++;
		if (m_object.count % 5 == 0)
		{
			m_object.count = 0;
			m_object.currentFrameX++;
			if (m_object.currentFrameX > IMAGEMANAGER->findImage("��Ʈ1 �ı�")->getMaxFrameX()) return true;
		}
	}
	return false;
}

//====================================================================   ��Ʈ2
HRESULT root2::init(POINT position)
{
	ZeroMemory(&m_object, sizeof(m_object));

	m_object.image = IMAGEMANAGER->findImage("��Ʈ2");
	m_object.x = position.x;
	m_object.y = position.y;
	m_object.rc = RectMake(m_object.x, m_object.y, 174, 74);
	m_object.hp = 100;
	m_object.count = m_object.currentFrameX = 0;
	m_object.current = ALIVE_OBJECT;
	m_object.isTeleport = false;
	return S_OK;
}

void root2::release()
{
}

void root2::update()
{
	m_object.rc = RectMake(m_object.x, m_object.y, 174, 74);

	animation();
	dead();
}

void root2::render(POINT pt)
{
	m_object.image->frameRender(getMemDC(), m_object.x - 40 - pt.x, m_object.y - 30 - pt.y, m_object.currentFrameX, 0);
}

void root2::animation()
{
	if (m_object.current == ALIVE_OBJECT)
	{
		if (67 <= m_object.hp) m_object.currentFrameX = 0;
		else if (34 <= m_object.hp && m_object.hp < 67) m_object.currentFrameX = 1;
		else if (0 < m_object.hp && m_object.hp < 34) m_object.currentFrameX = 2;
		else if (m_object.hp <= 0)
		{
			m_object.image = IMAGEMANAGER->findImage("��Ʈ2 �ı�");
			m_object.currentFrameX = 0;
			m_object.current = DEAD_OBJECT;
		}
	}
}

bool root2::dead()
{
	if (m_object.current == DEAD_OBJECT)
	{
		m_object.count++;
		if (m_object.count % 5 == 0)
		{
			m_object.count = 0;
			m_object.currentFrameX++;
			if (m_object.currentFrameX > IMAGEMANAGER->findImage("��Ʈ2 �ı�")->getMaxFrameX()) return true;
		}
	}
	return false;
}

//====================================================================   �ڷ���Ʈ
HRESULT teleport::init(POINT position)
{
	ZeroMemory(&m_object, sizeof(m_object));

	m_object.image = IMAGEMANAGER->findImage("�ڷ���Ʈ");
	m_object.x = position.x;
	m_object.y = position.y;
	m_object.rc = RectMake(m_object.x, m_object.y, 150, 100);
	m_object.isTeleport = true;
	return S_OK;
}

void teleport::release()
{
}

void teleport::update()
{
	m_object.rc = RectMake(m_object.x, m_object.y, 150, 100);
}

void teleport::render(POINT pt)
{
	m_object.image->render(getMemDC(), m_object.x - 30 - pt.x, m_object.y - 72 - pt.y);
}