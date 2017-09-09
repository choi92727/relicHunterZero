#pragma once
#include "gameNode.h"

struct St_menumBar
{
	RECT pre_Select;//���� ������ �簢��
	RECT aft_Select;//���콺 Ŀ���ö��� �簢��
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

