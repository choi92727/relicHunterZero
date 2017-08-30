#pragma once
#include "singletonBase.h"

class effect;

class effectManager : public singletonBase<effectManager>
{
private:
	//이펙트 클래스를 담은 벡터
	typedef vector<effect*> vEffect;
	typedef vector<effect*>::iterator viEffect;
	//이펙트 클래스가 담겨 있는 벡터를 담은 맵
	typedef map<string, vEffect> mEffect;
	typedef map<string, vEffect>::iterator miEffect;
	//모든 이펙트를 관리할 벡터(이펙트가 담겨 있는 벡터를 담은 맵을 다시 담은 벡터)
	typedef vector<mEffect> vTotalEffect;
	typedef vector<mEffect>::iterator viTotalEffect;

	//실제 모든 이펙트가 담겨 있는 벡터
	vTotalEffect m_vTotalEffect;
public:
	effectManager();
	~effectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//이펙트 추가(키 값, 이미지 이름, 이미지 가로크기, 세로크기, 한 프레임 가로크기, 세로크기, FPS. 이펙트 속도, 버퍼갯수)
	void addEffect(string effectKey, char* imageName, int imageW, int imageH, int frameW, int frameH, int FPS, float elapsedTime, int buffer);

	//이펙트 플레이(키 값, 좌표)
	void play(string effectKey, int x, int y);
};

