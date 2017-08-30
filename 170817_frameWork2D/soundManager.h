#pragma once
#include "singletonBase.h"
#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex_vc.lib")
using namespace FMOD;

//채널버퍼 및 사운드 버퍼
#define EXTRACHANNERBUFFER 5
#define SOUNDBUFFER 20

//총 사운드 버퍼 설정 : 버퍼가 작아서 씹히는 문제를 해결
#define TOTALSOUNDBUFFER SOUNDBUFFER * EXTRACHANNERBUFFER

class soundManager : public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;

	System* m_system;		//fmod의 시스템 클래스
	Sound** m_sound;		//fmod의 사운드 클래스
	Channel** m_channel;	//fmod의 채널 클래스

	arrSounds m_totalSound;	//맵에 담긴 사운드 목록

public:
	soundManager();
	~soundManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//사운드 추가(키값, 파일이름, BGM? , 루프?)
	void addSound(string keyName, string soundName, bool bgm = false, bool loop = false);

	//사운드 플레이(키값, 볼륨) 0.0~1.0
	void play(string keyName, float volume = 1.0f);
	//사운드 정지
	void stop(string keyName);
	//사운드 일시정지
	void pause(string keyName);
	//사운드 다시 재생
	void resume(string keyName);

	//플레이 중인지?
	bool isPlaySound(string keyName);
	//일시정지 중인지?
	bool isPauseSound(string keyName);
};