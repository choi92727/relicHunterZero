#include "stdafx.h"
#include "testScene.h"
#include "characterClassic.h"
testScene::testScene()
{
}


testScene::~testScene()
{
}

HRESULT testScene::init()
{
	POINT temp = { WINSIZEX / 2,WINSIZEY / 2 };
	m_player = new characterManager;
	m_player->init(temp, JIMMY);
	m_itemManager = new itemManager;
	m_itemManager->init();
	ptpt = { WINSIZEX / 2,WINSIZEY / 2 };

	rcrc = RectMakeCenter(ptpt.x, ptpt.y, 50, 100);
	return S_OK;
}

void testScene::release()
{
	m_player->release();
}

void testScene::update()
{
	//	m_player->update();
	m_itemManager->update();
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		m_itemManager->addItem(ptMouse);
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		ptpt.y -= 5;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		ptpt.y += 5;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		ptpt.x -= 5;

	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		ptpt.x += 5;
	}
	rcrc = RectMakeCenter(ptpt.x, ptpt.y, 50, 100);
	collisionDetect();
	SCENEMANAGER->changeScene("stageScene");
}

void testScene::render()
{
	//m_player->render();
	m_itemManager->render({ 0,0 });
	Rectangle(getMemDC(), rcrc.left, rcrc.top, rcrc.right, rcrc.bottom);
}

void testScene::collisionDetect()
{
	RECT tempRC;
	for (int i = 0; i < m_itemManager->getVEnemy().size(); i++)
	{
		if (IntersectRect(&tempRC, &m_itemManager->getVEnemy()[i]->getDetectRc(), &rcrc))
		{
			m_itemManager->getVEnemy()[i]->setX(m_itemManager->getVEnemy()[i]->getX() - (m_itemManager->getVEnemy()[i]->getX()- ptpt.x)/20);
			m_itemManager->getVEnemy()[i]->setY(m_itemManager->getVEnemy()[i]->getY() - (m_itemManager->getVEnemy()[i]->getY() - ptpt.y) / 20);
		}
	}
}
