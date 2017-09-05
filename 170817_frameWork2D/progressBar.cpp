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
	//체력바 위치 초기화
	m_x = x;
	m_y = y;

	//체력바 렉트 위치 및 크기 초기화
	m_rcProgress = RectMake(x, y, width, height);

	//체력바 이미지 추기화
	m_progressBarFront = IMAGEMANAGER->addImage("프론트이미지", frontImage, x, y, width, height, true, RGB(255, 0, 255));
	m_progressBarBack = IMAGEMANAGER->addImage("백이미지", backImage, x, y, width, height, true, RGB(255, 0, 255));

	//m_progressBarFront = new image;
	//m_progressBarFront->init(frontImage, x, y, width, height, true, RGB(255, 0, 255));
	//m_progressBarBack = new image;
	//m_progressBarBack->init(backImage, x, y, width, height, true, RGB(255, 0, 255));

	//가로 길이 초기화
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
		//프로그래스바 백이미지(변경될 필요 없다.)
		m_progressBarBack->render(getMemDC(), m_rcProgress.left + 1, m_y + 1, 0, 0, m_progressBarBack->getWidth(), m_progressBarBack->getHeight());
		//프로그래스바 프론즈 이미지(가로길이가 변경 되어야 한다.)
		m_progressBarFront->render(getMemDC(), m_rcProgress.left - 1, m_y - 1, 0, 0, m_width, m_progressBarBack->getHeight());

		//IMAGEMANAGER->render("백이미지", getMemDC(), m_rcProgress.left, m_y, 0, 0, m_progressBarBack->getWidth(), m_progressBarBack->getHeight());
		//IMAGEMANAGER->render("프론트이미지", getMemDC(), m_rcProgress.left, m_y, 0, 0, m_width, m_progressBarBack->getHeight());
	}
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	m_width = (currentGauge / maxGauge) * m_progressBarBack->getWidth();
	if (currentGauge == maxGauge || currentGauge <= 0) showBar = false;
	else showBar = true;
}