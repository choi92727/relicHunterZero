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
		int x, y;
		CHARACTER m_char;
		image m_image;
	};
	vector<bullet> m_vBullet;
public:	
	bulletInterface();
	~bulletInterface();
	virtual void fire(int x,int y,float angle,float speed);
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

