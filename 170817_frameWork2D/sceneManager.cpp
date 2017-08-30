#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

sceneManager::sceneManager()
{
}

sceneManager::~sceneManager()
{
}

//����ƽ ���� ������� �ΰ����� �ʱ�ȭ
gameNode* sceneManager::m_currentScene = nullptr;


HRESULT sceneManager::init()
{
	return S_OK;
}

void sceneManager::release()
{
	//�ݺ��ڸ� ���ؼ� ���� ���鼭 �ϳ��� �����Ѵ�.
	m_miSceneList iter = m_sceneList.begin();
	for (iter; iter != m_sceneList.end();)
	{
		//����
		if (iter->second != NULL)
		{
			if (iter->second == m_currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = m_sceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	m_sceneList.clear();
}

void sceneManager::update()
{
	if (m_currentScene) m_currentScene->update();
}

void sceneManager::render()
{
	if (m_currentScene) m_currentScene->render();
}

gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	if (!scene) return nullptr;

	m_sceneList.insert(make_pair(sceneName, scene));

	return nullptr;
}

HRESULT sceneManager::changeScene(string sceneName)
{
	m_miSceneList find = m_sceneList.find(sceneName);

	//�� ã������ fail
	if (find == m_sceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ������̶� ������ fail
	if (find->second == m_currentScene) return E_FAIL;

	//������� ������ ������ ������ ���� �ʱ�ȭ�ϰ� �������ش�.
	if (SUCCEEDED(find->second->init()))
	{
		//�������� ������ ������
		if (m_currentScene) m_currentScene->release();
		m_currentScene = find->second;

		return S_OK;
	}

	return E_NOTIMPL;
}
