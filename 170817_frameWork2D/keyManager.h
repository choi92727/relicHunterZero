#pragma once
#include "singletonBase.h"
#include <bitset>

#define KEY_MAX 256

using namespace std;

class keyManager : public singletonBase<keyManager>
{
private:
	bitset<KEY_MAX> m_keyUp;
	bitset<KEY_MAX> m_keyDown;
public:
	keyManager();
	~keyManager();

	HRESULT init();
	void release();

	bool isOnceKeyDown(int num);

	bool isOnceKeyUp(int num);

	bool isStayKeyDown(int num);

	bool isToggleKey(int num);
};

