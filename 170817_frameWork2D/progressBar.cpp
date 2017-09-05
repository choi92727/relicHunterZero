#include "stdafx.h"
#include "progressBar.h"

progressBar::progressBar()
{
}

progressBar::~progressBar()
{
}

HRESULT progressBar::init(char * frontImage, char * backImage, float x, float y, int width, int height)
{
	//ü�¹� ��ġ �ʱ�ȭ
	m_x = x;
	m_y = y;

	//ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
	m_rcProgress = RectMake(x, y, width, height);

	//ü�¹� �̹��� �߱�ȭ
	m_progressBarFront = IMAGEMANAGER->addImage("����Ʈ�̹���", frontImage, x, y, width, height, true, RGB(255, 0, 255));
	m_progressBarBack = IMAGEMANAGER->addImage("���̹���", backImage, x, y, width, height, true, RGB(255, 0, 255));

	//m_progressBarFront = new image;
	//m_progressBarFront->init(frontImage, x, y, width, height, true, RGB(255, 0, 255));
	//m_progressBarBack = new image;
	//m_progressBarBack->init(backImage, x, y, width, height, true, RGB(255, 0, 255));

	//���� ���� �ʱ�ȭ
	m_width = m_progressBarFront->getWidth();
	return S_OK;
}

void progressBar::release()
{
	//SAFE_DELETE(m_progressBarBack);
	//SAFE_DELETE(m_progressBarFront);
}

void progressBar::update()
{
	m_rcProgress = RectMakeCenter(m_x + m_progressBarBack->getWidth() / 2,
		m_y + m_progressBarBack->getHeight() / 2, m_progressBarBack->getWidth(), m_progressBarBack->getHeight());
}

void progressBar::render()
{
	if (showBar)
	{
		//���α׷����� ���̹���(����� �ʿ� ����.)
		m_progressBarBack->render(getMemDC(), m_rcProgress.left + 1, m_y + 1, 0, 0, m_progressBarBack->getWidth(), m_progressBarBack->getHeight());
		//���α׷����� ������ �̹���(���α��̰� ���� �Ǿ�� �Ѵ�.)
		m_progressBarFront->render(getMemDC(), m_rcProgress.left - 1, m_y - 1, 0, 0, m_width, m_progressBarBack->getHeight());

		//IMAGEMANAGER->render("���̹���", getMemDC(), m_rcProgress.left, m_y, 0, 0, m_progressBarBack->getWidth(), m_progressBarBack->getHeight());
		//IMAGEMANAGER->render("����Ʈ�̹���", getMemDC(), m_rcProgress.left, m_y, 0, 0, m_width, m_progressBarBack->getHeight());
	}
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	m_width = (currentGauge / maxGauge) * m_progressBarBack->getWidth();
	if (currentGauge == maxGauge || currentGauge <= 0) showBar = false;
	else showBar = true;
}