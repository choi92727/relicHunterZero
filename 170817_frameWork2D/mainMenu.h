#pragma once
#include "gameNode.h"

struct St_menumBar
{
	RECT pre_Select;//선택 이전의 사각형
	RECT aft_Select;//마우스 커서올라간후 사각형
	bool selected;
};

class mainMenu :
	public gameNode
	
{
private:
	St_menumBar m_Bar[4];
	image *mainLogo;
	animation* mainLogo_Ani;
	int loopx,loopy;
	

public:
	mainMenu();
	~mainMenu();

	HRESULT init();
	void release();
	void update();
	void render();
};

