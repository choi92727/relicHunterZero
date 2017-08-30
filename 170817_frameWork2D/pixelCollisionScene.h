#pragma once
#include "gameNode.h"

class pixelCollisionScene : public gameNode
{
private:
	image* m_ball;		//공
	RECT m_rc;

	float m_x, m_y;
	int m_probeY;		//픽셀충돌 감지할 y값

public:
	pixelCollisionScene();
	~pixelCollisionScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

