#include "stdafx.h"
#include "txtData.h"


txtData::txtData()
{
}


txtData::~txtData()
{
}

HRESULT txtData::init()
{
	return S_OK;
}

//한 줄짜리 데이터를 담아둘 것(모든 데이터를 한 줄 단위로 잘라서 지정)
void txtData::txtSave(char * saveFileName, vector<string> vStr)
{
	HANDLE file;
	char str[TXTLENGTH];
	DWORD write;

	strncpy_s(str, TXTLENGTH, vectorArrayCombine(vStr), TXTLENGTH);

	file = CreateFile(
		saveFileName,			//생성할 파일 또는 열 장치나 파일 이름
		GENERIC_WRITE,			//파일이나 장치를 만들거나 열 때 사용할 권한
		0,						//파일의 공유 모드 입력
		NULL,					//파일 또는 장치를 열 때 보안 및 특성
		CREATE_ALWAYS,			//파일이나 장치를 열 때 취할 행동
		FILE_ATTRIBUTE_NORMAL,	//파일이나 장치를 열 때 또는 만들 때 갖게될 특성
		NULL);					//만들어질 파일이 갖게될 특성 및 확장 특성에 대한 정보를 가지고 있는 템플릿 파일 핸들

	WriteFile(file, str, TXTLENGTH, &write, NULL);
	CloseHandle(file);
}

//현재 사용할 데이터(한 줄짜리 데이터를 쉼표 단위로 띄어서 저장)
char * txtData::vectorArrayCombine(vector<string> vArray)
{
	char str[TXTLENGTH];
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, TXTLENGTH, vArray[i].c_str(), TXTLENGTH);
		if ((i + 1) < vArray.size())
		{
			strcat(str, ", ");
		}
	}
	return str;
}

vector<string> txtData::txtLoad(char * loadFileName)
{
	HANDLE file;
	char str[TXTLENGTH];
	DWORD read;

	ZeroMemory(str, sizeof(str));

	file = CreateFile(
		loadFileName,			//생성할 파일 또는 열 장치나 파일 이름
		GENERIC_READ,			//파일이나 장치를 만들거나 열 때 사용할 권한
		0,						//파일의 공유 모드 입력
		NULL,					//파일 또는 장치를 열 때 보안 및 특성
		OPEN_EXISTING,			//파일이나 장치를 열 때 취할 행동
		FILE_ATTRIBUTE_NORMAL,	//파일이나 장치를 열 때 또는 만들 때 갖게될 특성
		NULL);					//만들어질 파일이 갖게될 특성 및 확장 특성에 대한 정보를 가지고 있는 템플릿 파일 핸들

	ReadFile(file, str, TXTLENGTH, &read, NULL);
	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;
	char* separator = ", ";
	char* token;

	token = strtok(charArray, separator);
	vArray.push_back(token);

	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}
	return vArray;
}
