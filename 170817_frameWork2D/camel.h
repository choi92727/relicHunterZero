#pragma once
#include "gameNode.h"
class camel : public gameNode
{
private:
	image* m_camel;

	//animation* m_ani1;
	//animation* m_ani2;
	//animation* m_ani3;
	animation* m_ani;

public:
	camel();
	~camel();

	HRESULT init();
	void release();
	void update();
	void render();

};

