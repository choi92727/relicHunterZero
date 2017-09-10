#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	return S_OK;
}

void itemManager::release()
{
	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end();)
	{
		 m_viItem = m_vItem.erase(m_viItem);
		
	}
}

void itemManager::update()
{
	
	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end(); m_viItem++)
	{
		(*m_viItem)->update();
	}
	this->pickItem();
}

void itemManager::render(POINT pt)
{
	RECT temp;
	RECT camera_rc = RectMake(pt.x, pt.y, 1280, 720);
	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end(); m_viItem++)
	{
		if (IntersectRect(&temp, &camera_rc, &(*m_viItem)->getRealRc()))
		{
		(*m_viItem)->render(pt);

		}
	}
}

void itemManager::addItem(POINT position)
{
	switch (RND->getInt(4))
	{
	case 0:
		ammo0* m_ammo0;
		m_ammo0 = new ammo0;
		m_ammo0->init(position);
		m_vItem.push_back(m_ammo0);
		break;
	case 1:
		ammo1* m_ammo1;
		m_ammo1 = new ammo1;
		m_ammo1->init(position);
		m_vItem.push_back(m_ammo1);
		break;
	case 2:
		ammo2* m_ammo2;
		m_ammo2 = new ammo2;
		m_ammo2->init(position);
		m_vItem.push_back(m_ammo2);
		break;
	case 3:
		health* m_health;
		m_health = new health;
		m_health->init(position);
		m_vItem.push_back(m_health);
		break;
	}
}

void itemManager::pickItem()
{
	m_viItem = m_vItem.begin();
	for (m_viItem; m_viItem != m_vItem.end();)
	{
		if ((*m_viItem)->getPick()) m_viItem = m_vItem.erase(m_viItem);
		else m_viItem++;
	}
}


