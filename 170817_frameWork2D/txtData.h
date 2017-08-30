#pragma once
#include "singletonBase.h"
#define TXTLENGTH 131072

class txtData : public singletonBase<txtData>
{
public:
	txtData();
	~txtData();

	HRESULT init();
	//세이브
	void txtSave(char* saveFileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	//로드
	//한 줄에 넣을 데이터
	vector<string> txtLoad(char* loadFileName);
	//그 데이터들의 리스트
	vector<string> charArraySeparation(char charArray[]);
};

