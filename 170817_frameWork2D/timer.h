#pragma once

class timer
{
private:
	bool m_isHardware;				//���� Ÿ�̸Ӹ� �����ϳ�?
	float m_timeScale;				//�ð������
	float m_timeElapsed;			//�� �����Ӵ� �����
	__int64 m_curTime;				//����ð�
	__int64 m_lastTime;				//������ �ð�
	__int64 m_periodFrequncy;		//�ð��ֱ�

	unsigned long m_frameRate;		//FPS
	unsigned long m_FPSframeCount;	//FPS ī��Ʈ
	float m_FPStimeElapsed;			//FPS ������ �ð��� ���� �ð��� �����
	float m_worldTime;				//��ü �ð� �����

public:
	timer();
	~timer();

	HRESULT init();

	//���� �ð� ���
	void tick(float lockFPS = 0.0f);
	//���� FPS ��������
	unsigned long getFrameRate(char* str = nullptr) const;
	//�������Ӵ� ��� �ð�
	float getElapsedTime() const { return m_timeElapsed; }
	//��ü ��� �ð� ��������
	float getWorldTime() const { return m_worldTime; }
};