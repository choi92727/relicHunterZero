#pragma once
#include "gameNode.h"
class bulletInterface : public gameNode
{

protected:
	struct bullet
	{
		float m_speed;
		float m_angle;
		float m_damage;
		float m_range;
		float m_width;
		float m_height;
		float m_isGravity;
		float m_gravity;
		int m_x, m_y;
		CHARACTER m_playerType;
		animation *m_ani;
		image* m_image;
	};
	Image* m_bulletImage;
	Graphics* m_graphics;
	typedef vector<bullet*> vBullet;
	typedef vector<bullet*>::iterator viBullet;
	vBullet m_vBullet;
	viBullet m_viBullet;
public:	
	bulletInterface();
	~bulletInterface();
	virtual void fire(int x,int y,float angle,float speed,CHARACTER playerType);
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void delBullet(viBullet &delBullet);
	virtual int getBulletSize();


	RECT getRect(viBullet &rectBullet)
	{
		RECT temp = RectMake((*rectBullet)->m_x, (*rectBullet)->m_y,
			(*rectBullet)->m_x + (*rectBullet)->m_width, (*rectBullet)->m_y + (*rectBullet)->m_height);
		return temp;
	}
	CHARACTER getType(viBullet &typeBullet)
	{
		return (*typeBullet)->m_playerType;
	}
	float getDamage(viBullet &dmgBullet)
	{
		return (*dmgBullet)->m_damage;
	}


};

