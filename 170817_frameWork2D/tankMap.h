#pragma once
#include "gameNode.h"
#include "tileNode.h"
class tankMap :
	public gameNode
{
private:
	DWORD m_attribute[TILEX * TILEY];
	tagTile m_tiles[TILEX * TILEY];
	
	int m_pos[2];
public:
	tankMap();
	~tankMap();

	HRESULT init();
	void release();
	void update();
	void render();

	void load();


	tagTile* getTile() { return m_tiles; }
	int getPosFirst() { return 0; }

	DWORD* getAttribute() { return m_attribute; }

};

