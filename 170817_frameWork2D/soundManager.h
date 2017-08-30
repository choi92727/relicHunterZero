#pragma once
#include "singletonBase.h"
#include "inc/fmod.hpp"
#pragma comment(lib, "lib/fmodex_vc.lib")
using namespace FMOD;

//ä�ι��� �� ���� ����
#define EXTRACHANNERBUFFER 5
#define SOUNDBUFFER 20

//�� ���� ���� ���� : ���۰� �۾Ƽ� ������ ������ �ذ�
#define TOTALSOUNDBUFFER SOUNDBUFFER * EXTRACHANNERBUFFER

class soundManager : public singletonBase<soundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;

	System* m_system;		//fmod�� �ý��� Ŭ����
	Sound** m_sound;		//fmod�� ���� Ŭ����
	Channel** m_channel;	//fmod�� ä�� Ŭ����

	arrSounds m_totalSound;	//�ʿ� ��� ���� ���

public:
	soundManager();
	~soundManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//���� �߰�(Ű��, �����̸�, BGM? , ����?)
	void addSound(string keyName, string soundName, bool bgm = false, bool loop = false);

	//���� �÷���(Ű��, ����) 0.0~1.0
	void play(string keyName, float volume = 1.0f);
	//���� ����
	void stop(string keyName);
	//���� �Ͻ�����
	void pause(string keyName);
	//���� �ٽ� ���
	void resume(string keyName);

	//�÷��� ������?
	bool isPlaySound(string keyName);
	//�Ͻ����� ������?
	bool isPauseSound(string keyName);
};