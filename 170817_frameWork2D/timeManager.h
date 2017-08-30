#pragma once
#include "singletonBase.h"
#include "timer.h"

class timeManager : public singletonBase<timeManager>
{
private:
	timer* m_timer;

public:
	timeManager();
	~timeManager();

	HRESULT init();
	void release();
	void update(float lock = 0.0f);
	void render(HDC hdc);

	//�� �����Ӵ� ����ð� �������� 1/60
	float getElasedTime() const { return m_timer->getElapsedTime(); }
	//��ü �ð� ����� ��������
	float getWorldTime() const { return m_timer->getWorldTime(); }
};

