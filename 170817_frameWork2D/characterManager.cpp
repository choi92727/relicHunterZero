#include "stdafx.h"
#include "characterManager.h"
#include "characterClassic.h"

characterManager::characterManager()
{
}


characterManager::~characterManager()
{
}

HRESULT characterManager::init(POINT position, selectCharacter chara)
{
	switch (chara)	//stdafx에 enum문으로 캐릭터 선언함
	{
	case JIMMY:
		m_player = new jimmy;
		break;
	case RIDER:
		m_player = new rider;
		break;
	}

	m_player->init(position);
	return S_OK;
}

void characterManager::release()
{
	SAFE_DELETE(m_player);
}

void characterManager::update(POINT pt)
{
	m_player->update(pt);
}

void characterManager::render(POINT pt)
{
	m_player->render(pt);
}
