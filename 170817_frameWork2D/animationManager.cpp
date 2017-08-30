#include "stdafx.h"
#include "animationManager.h"

animationManager::animationManager()
{
}

animationManager::~animationManager()
{
}

HRESULT animationManager::init()
{
	return S_OK;
}

void animationManager::release()
{
	deleteAll();
}

void animationManager::update()
{
	arrAnimationIter iter = m_animation.begin();
	for (iter; iter != m_animation.end(); ++iter)
	{
		if (!iter->second->isPlay()) continue;
		iter->second->frameUpdate(TIMEMANAGER->getElasedTime() * 1.0f);
	}
}

void animationManager::render()
{
}

void animationManager::addDefAnimation(string animationKeyName, char * imageKeyName, int fps, bool reverse, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	m_animation.insert(make_pair(animationKeyName, ani));
}

void animationManager::addAnimation(string animationKeyName, char * imageKeyName, int * playArr, int arrLen, int fps, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(playArr, arrLen, loop);
	ani->setFPS(fps);

	m_animation.insert(make_pair(animationKeyName, ani));
}

void animationManager::addAnimation(string animationKeyName, char * imageKeyName, int start, int end, int fps, bool reverse, bool loop)
{
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	m_animation.insert(make_pair(animationKeyName, ani));
}

void animationManager::start(string animationKeyName)
{
	arrAnimationIter iter = m_animation.find(animationKeyName);
	iter->second->start();
}

void animationManager::stop(string animationKeyName)
{
	arrAnimationIter iter = m_animation.find(animationKeyName);
	iter->second->stop();
}

void animationManager::pause(string animationKeyName)
{
	arrAnimationIter iter = m_animation.find(animationKeyName);
	iter->second->pause();
}

void animationManager::resume(string animationKeyName)
{
	arrAnimationIter iter = m_animation.find(animationKeyName);
	iter->second->resume();
}

animation * animationManager::findAnimation(string animationKeyName)
{
	arrAnimationIter iter = m_animation.find(animationKeyName);
	if (iter != m_animation.end())
	{
		return iter->second;
	}
	return nullptr;
}

void animationManager::deleteAll()
{
	arrAnimationIter iter = m_animation.begin();
	for (iter; iter != m_animation.end();)
	{
		if (iter->second != NULL)
		{
			SAFE_DELETE(iter->second);
			iter = m_animation.erase(iter);
		}

		else
		{
			++iter;
		}
	}
}
