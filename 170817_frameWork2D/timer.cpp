#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

//timeGetTime �Լ��� ����ϱ� ���� ���̺귯�� �߰�
//�����찡 ���۵ǰ� �� ���� �ð��� ����


timer::timer()
{
}


timer::~timer()
{
}

HRESULT timer::init()
{
	//���� Ÿ�̸� �������θ� ġũ�Ѵ�.
	//���� Ÿ�̸Ӹ� �����ϸ� �ʴ� ����ũ�μ�������� ���� ����. (1/1000000)
	//�ð� ����
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_periodFrequncy))
	{
		//64��Ʈ ������ ����� �� �ֵ��� ������ ������
		//����ũ�� �����带(1/1000000)�� ���� �����Ͽ� �� �� ��Ȯ�� �ð����� �����ϱ� ����)
		m_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_lastTime);

		//�ʴ� �ð� ��� ����
		m_timeScale = 1.0f / m_periodFrequncy;
	}
	else
	{
		m_isHardware = false;
		//�и������� ������ �ð����� �ʴ� 1000�� ī��Ʈ
		m_lastTime = timeGetTime();
		m_timeScale = 0.001f;
	}

	m_frameRate = 0;
	m_FPSframeCount = 0;
	m_FPStimeElapsed = 0.0f;
	m_worldTime = 0;

	return S_OK;
}

void timer::tick(float lockFPS)
{
	//���� Ÿ�̸Ӹ� �����Ѵٸ�
	if (m_isHardware)
	{
		//�� ���� ����ũ���� ������ ���
		QueryPerformanceCounter((LARGE_INTEGER*)&m_curTime);
	}
	else
	{
		//�������� ������ time�Լ��� �̿� �и�������
		m_curTime = timeGetTime();
	}

	m_timeElapsed = (m_curTime - m_lastTime) * m_timeScale;

	if (lockFPS > 0.0f)
	{
		//���� ������ �ð��� ������ ������ �������Ѷ�
		while (m_timeElapsed < (1.0f / lockFPS))
		{
			if (m_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&m_curTime);
			else m_curTime = timeGetTime();

			//������ �ð��� ����ð��� �����
			m_timeElapsed = (m_curTime - m_lastTime) * m_timeScale;
		}
	}

	m_lastTime = m_curTime;				//������ �ð��� ���
	m_FPSframeCount++;					//�ڵ����� ������ ī��Ʈ ����
	m_FPStimeElapsed += m_timeElapsed;	//�ʴ� ������ �ð� ����� ����
	m_worldTime += m_timeElapsed;		//��ü �ð� ����� ����

	if (m_FPStimeElapsed > 1.0f)
	{
		m_frameRate = m_FPSframeCount;
		m_FPSframeCount = 0;
		m_FPStimeElapsed = 0.0f;
	}
}

unsigned long timer::getFrameRate(char * str) const
{
	if (str != nullptr)
	{
		wsprintf(str, "FPS: %d", m_frameRate);
	}

	return m_frameRate;
}
