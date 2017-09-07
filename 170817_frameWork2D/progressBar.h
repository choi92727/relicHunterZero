#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT m_rcProgress;	//ü�¹� ��Ʈ
	int m_x, m_y;		//ü�¹� ��ǥ
	int m_width;		//ü�¹� ���α���(�̰ɷ� ����)

	image* m_progressBarFront;	//ü�¹� �� �̹���
	image* m_progressBarBack;	//ü�¹� �� �̹���
public:
	progressBar();
	~progressBar();

	//ü�¹� �ʱ�ȭ(���̹���, ���̹���, x,y,���α���,���α���)
	HRESULT init(char* frontImage, char* backImage, float x, float y, int width, int height);
	void release();
	void update();
	void render(POINT pt);

	//���α׷����� ������ ����!
	void setGauge(float currentGauge, float maxGauge);

	//���α׷��� ��ġ
	void setX(int x) { m_x = x; }
	void setY(int y) { m_y = y; }

	RECT getRect() { return m_rcProgress; }

};

