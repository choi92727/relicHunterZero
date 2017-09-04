#pragma once
#include "gameNode.h"
enum select_currentType
{
	jimmy_selected,
	rider_selected,
	non_selected

};
class selectScene :
	public gameNode
{
private:
	int loopX;
	int loopY;
	RECT select_Rc[2];
	RECT start_Rc;
	RECT change_Rc;
	RECT cancel_Rc;

	image * im_rider;
	image * im_jimmy;

	animation* ani_rider;
	animation* ani_jimmy;

	select_currentType s_Ct;

public:
	selectScene();
	~selectScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void moveStar();
	void aniSelectBar();
	void selectRender();

	void goJimmy();
	void goRider();
};

