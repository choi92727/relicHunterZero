#pragma once
#include "gameNode.h"
#include "object.h"

class objectManager : public gameNode
{
private:
	vector<object*> m_vObject;
	vector<object*>::iterator m_viObject;
public:
	objectManager();
	~objectManager();

	HRESULT init();
	void release();
	void update();
	void render(POINT pt);

	void deleteObject();

	void addBox1(POINT pt);
	void addBox2(POINT pt);
	void addRoot1(POINT pt);
	void addRoot2(POINT pt);
	void addTeleport(POINT pt);

	vector<object*> getVObject() { return m_vObject; }
	vector<object*>::iterator getViObject() { return m_viObject; }
};

