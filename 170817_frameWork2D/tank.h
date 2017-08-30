#pragma once
#include "tankMap.h"
#include "gameNode.h"
enum TANKDIRECTION
{
	TANKDIRECTION_LEFT,
	TANKDIRECTION_RIGHT,
	TANKDIRECTION_UP,
	TANKDIRECTION_DOWN,

};
class tank :public gameNode
{
private:
	TANKDIRECTION m_direction;
	image* m_image;
	RECT m_rc;
	float m_x, m_y;
	float m_speed;
	tankMap * m_tankMap;
public:
	tank();
	~tank();

	HRESULT init();
	void release();
	void update();
	void render();

	void tankMove();
	void setTankPosition();
	void setTankMapMemoryLink(tankMap* tm) { m_tankMap = tm; }

	bool findUnmoveTile();
};

