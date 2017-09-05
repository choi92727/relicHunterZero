#pragma once
#include "gameNode.h"
class cursorDraw :public gameNode
{
private:
	image* cursor_im;
	animation* cursor_ani;
public:
	cursorDraw();
	~cursorDraw();

	HRESULT init(int x);
	void release();
	void update();
	void render();

	bool reload();
};

