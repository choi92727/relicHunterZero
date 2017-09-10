#pragma once
#include "gameNode.h"
#include "item.h"
class itemManager :
	public gameNode
{
private:
	vector<item*> m_vItem;
	vector<item*>::iterator m_viItem;
public:
	itemManager();
	~itemManager();
	HRESULT init();
	void release();
	void update();
	void render(POINT pt);

	void addItem(POINT position);

	void pickItem();

	vector<item*> getVEnemy() { return m_vItem; }
	vector<item*>::iterator getViEnemy() { return m_viItem; }
};

