#pragma once
#include "singletonBase.h"

//게임노드 전방선언
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
private:
	typedef map<string, gameNode*> m_mSceneList;
	typedef map<string, gameNode*>::iterator m_miSceneList;

	static gameNode* m_currentScene;		//현재씬
	m_mSceneList m_sceneList;				//씬 목록

public:
	sceneManager();
	~sceneManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//씬추가
	gameNode* addScene(string sceneName, gameNode* scene);
	//씬 변경
	HRESULT changeScene(string sceneName);


};