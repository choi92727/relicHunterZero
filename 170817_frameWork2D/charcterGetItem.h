#pragma once
#include "gameNode.h"
class charcterGetItem :
	public gameNode
{
private:
	image* m_im;
	animation* m_ani;
	bool m_can;

	POINT m_pt;
public:
	charcterGetItem();
	~charcterGetItem();

	HRESULT init();
	void release();
	void update(float x, float y);
	void render(POINT pt);

	void canGet(bool x) { m_can = x; }
};

