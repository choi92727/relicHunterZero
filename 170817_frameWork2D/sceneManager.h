#pragma once
#include "singletonBase.h"

//���ӳ�� ���漱��
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
private:
	typedef map<string, gameNode*> m_mSceneList;
	typedef map<string, gameNode*>::iterator m_miSceneList;

	static gameNode* m_currentScene;		//�����
	m_mSceneList m_sceneList;				//�� ���

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//���߰�
	gameNode* addScene(string sceneName, gameNode* scene);
	//�� ����
	HRESULT changeScene(string sceneName);


};