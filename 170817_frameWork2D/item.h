#pragma once
#include "gameNode.h"
enum ITEMTYPE
{
	AMMO0,
	AMMO1,
	AMMO2,
	HEALTH
};

class item :
	public gameNode
{
protected:
	image* m_im;
	float m_x, m_y;
	float startX, startY;
	RECT real_rc;
	RECT detect_rc;
	float speed;
	float speedX;
	bool isDetect;
	bool born;
	ITEMTYPE m_type;
	bool pick;
public:
	item();
	~item();

	virtual HRESULT init(POINT position);
	virtual void release();
	virtual void update();
	virtual void render(POINT pt);

	virtual float getX() { return m_x; }
	virtual void setX(float a) { m_x = a; }
	virtual float getY() { return m_y; }
	virtual void setY(float a) { m_y = a; }
	virtual RECT getRealRc() { return real_rc; }
	virtual RECT getDetectRc() { return detect_rc; }
	virtual float getSpeed() { return speed; }
	virtual bool getIsDetect() { return isDetect; }
	virtual void setIsDetect(bool x) { isDetect = x; }
	virtual ITEMTYPE getType() { return m_type; }
	virtual bool getBorn() { return born; }
	virtual void setPick() { pick = true; }
	virtual bool getPick() { return pick; }
};


class ammo0 : public item
{
private:
public:
	ammo0();
	~ammo0();

	HRESULT init(POINT position);
	void release();
	void update();
	void render(POINT pt);
};

class ammo1 : public item
{
private:
public:
	ammo1();
	~ammo1();

	HRESULT init(POINT position);
	void release();
	void update();
	void render(POINT pt);
};

class ammo2 : public item
{
private:
public:
	ammo2();
	~ammo2();

	HRESULT init(POINT position);
	void release();
	void update();
	void render(POINT pt);
};

class health : public item
{
private:
public:
	health();
	~health();

	HRESULT init(POINT position);
	void release();
	void update();
	void render(POINT pt);
};


