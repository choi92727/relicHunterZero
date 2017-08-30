#pragma once
#include "singletonBase.h"
#include "image.h"

class animationManager : public singletonBase<animationManager>
{
private:
	typedef map<string, animation*> arrAnimation;
	typedef map<string, animation*>::iterator arrAnimationIter;

	arrAnimation m_animation;

public:
	animationManager();
	~animationManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//처음부터 끝가지
	void addDefAnimation(string animationKeyName, char* imageKeyName, int fps, bool reverse = false, bool loop = false);
	//배열에 담아서
	void addAnimation(string animationKeyName, char* imageKeyName, int* playArr, int arrLen, int fps, bool loop = false);
	//구간 정해서
	void addAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps, bool reverse = false, bool loop = false);

	void start(string animationKeyName);
	void stop(string animationKeyName);
	void pause(string animationKeyName);
	void resume(string animationKeyName);

	//애니메이션 찾기
	animation* findAnimation(string animationKeyName);

	//애니메이션 찾기삭제
	void deleteAll();
};

