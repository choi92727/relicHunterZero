#pragma once
#include "gameNode.h"
class teleport :
	public gameNode
{
private:
	RECT m_rc;
	RECT detect_rc;
	
	image* m_im;
	animation* m_ani;
	int frameX;
public:
	teleport();
	~teleport();

	HRESULT init();
	void release();
	void update();
	void render();
};

