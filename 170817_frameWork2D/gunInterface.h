#pragma once
#include "gameNode.h"
class gunInterface : public gameNode
{
protected:
	float m_damage;
	float m_speed;
	float m_angle;
	float m_x;
	float m_y;
	float m_width;
	float m_height;
	float m_range;
public:
	gunInterface();
	~gunInterface();
	virtual void fire();
	virtual void setAngle();
	virtual void setPosition(int x,int y);
};

