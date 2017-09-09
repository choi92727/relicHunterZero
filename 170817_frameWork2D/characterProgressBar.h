#pragma once
#include"gameNode.h"
class characterProgressBar : public gameNode
{
private:
	RECT m_rcProgress;	//체력바 렉트
	int m_x, m_y;		//체력바 좌표
	int m_width;		//체력바 가로길이(이걸로 조정)

	image* m_progressBarFront;	//체력바 앞 이미지
	image* m_progressBarBack;	//체력바 뒤 이미지
public:
	characterProgressBar();
	~characterProgressBar();

	//체력바 초기화(앞이미지, 백이미지, x,y,가로길이,세로길이)
	HRESULT init(string frontImage, string backImage, float x, float y, int width, int height);
	void release();
	void update();
	void render();

	//프로그래스바 게이지 셋팅!
	void setGauge(float currentGauge, float maxGauge);

	//프로그래바 위치
	void setX(int x) { m_x = x; }
	void setY(int y) { m_y = y; }

	RECT getRect() { return m_rcProgress; }

};
