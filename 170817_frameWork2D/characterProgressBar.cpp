#include "stdafx.h"
#include "characterProgressBar.h"


characterProgressBar::characterProgressBar()
{
}


characterProgressBar::~characterProgressBar()
{
}

HRESULT characterProgressBar::init(string frontImage, string backImage, float x, float y, int width, int height)
{
	//ü�¹� ��ġ �ʱ�ȭ
	m_x = x;
	m_y = y;

	//ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
	m_rcProgress = RectMake(x, y, width, height);

	//ü�¹� �̹��� �߱�ȭ
	m_progressBarFront = IMAGEMANAGER->findImage(frontImage);
	m_progressBarBack = IMAGEMANAGER->findImage(backImage);

	//m_progressBarFront = new image;
	//m_progressBarFront->init(frontImage, x, y, width, height, true, RGB(255, 0, 255));
	//m_progressBarBack = new image;
	//m_progressBarBack->init(backImage, x, y, width, height, true, RGB(255, 0, 255));

	//���� ���� �ʱ�ȭ
	m_width = m_progressBarFront->getWidth();
	return S_OK;
}

void characterProgressBar::release()
{
}

void characterProgressBar::update()
{
	m_rcProgress = RectMakeCenter(m_x + m_progressBarBack->getWidth() / 2,
		m_y + m_progressBarBack->getHeight() / 2, m_progressBarBack->getWidth(), m_progressBarBack->getHeight());
}

void characterProgressBar::render()
{
	m_progressBarBack->alphaRender(getMemDC(), m_rcProgress.left + 1, m_y + 1, 0, 0, m_progressBarBack->getWidth(), m_progressBarBack->getHeight(),100);
	//���α׷����� ������ �̹���(���α��̰� ���� �Ǿ�� �Ѵ�.)
	m_progressBarFront->render(getMemDC(), m_rcProgress.left - 1, m_y - 1, 0, 0, m_width, m_progressBarBack->getHeight());

}

void characterProgressBar::setGauge(float currentGauge, float maxGauge)
{
	m_width = (currentGauge / maxGauge) * m_progressBarBack->getWidth();
}
