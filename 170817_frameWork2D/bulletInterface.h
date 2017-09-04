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
		int m_x, m_y;
		CHARACTER m_char;
		image m_image;
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
	virtual void fire(int x,int y,float angle,float speed);
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void delBullet(viBullet &delBullet);


};

