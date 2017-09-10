#include "stdafx.h"
#include "objectManager.h"


objectManager::objectManager()
{
}


objectManager::~objectManager()
{
}

HRESULT objectManager::init()
{
	return S_OK;
}

void objectManager::release()
{
	m_viObject = m_vObject.begin();
	for (m_viObject; m_viObject != m_vObject.end();)
	{
		(*m_viObject)->release();
	}
}

void objectManager::update()
{
	m_viObject = m_vObject.begin();
	for (m_viObject; m_viObject != m_vObject.end(); m_viObject++)
	{
		(*m_viObject)->update();
	}
	this->deleteObject();
}

void objectManager::render(POINT pt)
{
	RECT temp;
	RECT camera_rc =  RectMake(pt.x, pt.y, 1280, 720);
	m_viObject = m_vObject.begin();
	for (m_viObject; m_viObject != m_vObject.end(); m_viObject++)
	{
		if (IntersectRect(&temp, &camera_rc, &(*m_viObject)->getRect()))
		{

			(*m_viObject)->render(pt);
		}
		
	
	}
}

void objectManager::deleteObject()
{
	m_viObject = m_vObject.begin();
	for (m_viObject; m_viObject != m_vObject.end();)
	{
		if ((*m_viObject)->dead()) m_viObject = m_vObject.erase(m_viObject);
		else m_viObject++;
	}
}

//박스1 추가
void objectManager::addBox1(POINT pt)
{
	box1* m_box1;
	m_box1 = new box1;
	m_box1->init(pt);
	m_vObject.push_back(m_box1);
}

//박스2 추가
void objectManager::addBox2(POINT pt)
{
	box2* m_box2;
	m_box2 = new box2;
	m_box2->init(pt);
	m_vObject.push_back(m_box2);
}

//루트1 추가
void objectManager::addRoot1(POINT pt)
{
	root1* m_root1;
	m_root1 = new root1;
	m_root1->init(pt);
	m_vObject.push_back(m_root1);
}

//루트2 추가
void objectManager::addRoot2(POINT pt)
{
	root2* m_root2;
	m_root2 = new root2;
	m_root2->init(pt);
	m_vObject.push_back(m_root2);
}

//텔레포트 추가
void objectManager::addTeleport(POINT pt)
{
	teleport* m_teleport;
	m_teleport = new teleport;
	m_teleport->init(pt);
	m_vObject.push_back(m_teleport);
}
