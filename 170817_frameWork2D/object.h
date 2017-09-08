#pragma once
#include "gameNode.h"

enum currentObject
{
	ALIVE_OBJECT,
	DEAD_OBJECT
};

//오브젝트 구조체
struct tagObject
{
	image* image;
	RECT rc;
	float x, y;
	int hp;
	int count;
	int currentFrameX;
	currentObject current;
	bool isTeleport;
};

class object : public gameNode
{
private:
	tagObject m_object;
public:
	object();
	virtual ~object();

	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render(POINT pt);

	virtual void animation();
	virtual bool dead();

	//오브젝트 체력 감소
	virtual void setHP(int hp) { if (m_object.current == ALIVE_OBJECT) m_object.hp = m_object.hp - hp; }
	
	//오브젝트 렉트
	virtual RECT getRect() { return m_object.rc; }

	//오브젝트 텔레포트냐?
	virtual bool getIsTeleport() { return m_object.isTeleport; }
};

class box1 : public object
{
private:
	tagObject m_object;
public:
	HRESULT init(POINT position);
	void release();
	void update();
	void render(POINT pt);

	void animation();
	bool dead();

	//오브젝트 체력 감소
	void setHP(int hp) { if (m_object.current == ALIVE_OBJECT) m_object.hp = m_object.hp - hp; }

	//오브젝트 렉트
	RECT getRect() { return m_object.rc; }

	//오브젝트 텔레포트냐?
	bool getIsTeleport() { return m_object.isTeleport; }
};

class box2 : public object
{
private:
	tagObject m_object;
public:
	HRESULT init(POINT position);
	void release();
	void update();
	void render(POINT pt);

	void animation();
	bool dead();

	//오브젝트 체력 감소
	void setHP(int hp) { if (m_object.current == ALIVE_OBJECT) m_object.hp = m_object.hp - hp; }

	//오브젝트 렉트
	RECT getRect() { return m_object.rc; }

	//오브젝트 텔레포트냐?
	bool getIsTeleport() { return m_object.isTeleport; }
};

class root1 : public object
{
private:
	tagObject m_object;
public:
	HRESULT init(POINT position);
	void release();
	void update();
	void render(POINT pt);

	void animation();
	bool dead();

	//오브젝트 체력 감소
	void setHP(int hp) { if (m_object.current == ALIVE_OBJECT) m_object.hp = m_object.hp - hp; }

	//오브젝트 렉트
	RECT getRect() { return m_object.rc; }

	//오브젝트 텔레포트냐?
	bool getIsTeleport() { return m_object.isTeleport; }
};

class root2 : public object
{
private:
	tagObject m_object;
public:
	HRESULT init(POINT position);
	void release();
	void update();
	void render(POINT pt);

	void animation();
	bool dead();

	//오브젝트 체력 감소
	void setHP(int hp) { if (m_object.current == ALIVE_OBJECT) m_object.hp = m_object.hp - hp; }

	//오브젝트 렉트
	RECT getRect() { return m_object.rc; }

	//오브젝트 텔레포트냐?
	bool getIsTeleport() { return m_object.isTeleport; }
};

class teleport : public object
{
private:
	tagObject m_object;
public:
	HRESULT init(POINT position);
	void release();
	void update();
	void render(POINT pt);

	//오브젝트 렉트
	RECT getRect() { return m_object.rc; }

	//오브젝트 텔레포트냐?
	bool getIsTeleport() { return m_object.isTeleport; }
};