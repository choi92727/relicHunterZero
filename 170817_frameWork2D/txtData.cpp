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

//�� ��¥�� �����͸� ��Ƶ� ��(��� �����͸� �� �� ������ �߶� ����)
void txtData::txtSave(char * saveFileName, vector<string> vStr)
{
	HANDLE file;
	char str[TXTLENGTH];
	DWORD write;

	strncpy_s(str, TXTLENGTH, vectorArrayCombine(vStr), TXTLENGTH);

	file = CreateFile(
		saveFileName,			//������ ���� �Ǵ� �� ��ġ�� ���� �̸�
		GENERIC_WRITE,			//�����̳� ��ġ�� ����ų� �� �� ����� ����
		0,						//������ ���� ��� �Է�
		NULL,					//���� �Ǵ� ��ġ�� �� �� ���� �� Ư��
		CREATE_ALWAYS,			//�����̳� ��ġ�� �� �� ���� �ൿ
		FILE_ATTRIBUTE_NORMAL,	//�����̳� ��ġ�� �� �� �Ǵ� ���� �� ���Ե� Ư��
		NULL);					//������� ������ ���Ե� Ư�� �� Ȯ�� Ư���� ���� ������ ������ �ִ� ���ø� ���� �ڵ�

	WriteFile(file, str, TXTLENGTH, &write, NULL);
	CloseHandle(file);
}

//���� ����� ������(�� ��¥�� �����͸� ��ǥ ������ �� ����)
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
		loadFileName,			//������ ���� �Ǵ� �� ��ġ�� ���� �̸�
		GENERIC_READ,			//�����̳� ��ġ�� ����ų� �� �� ����� ����
		0,						//������ ���� ��� �Է�
		NULL,					//���� �Ǵ� ��ġ�� �� �� ���� �� Ư��
		OPEN_EXISTING,			//�����̳� ��ġ�� �� �� ���� �ൿ
		FILE_ATTRIBUTE_NORMAL,	//�����̳� ��ġ�� �� �� �Ǵ� ���� �� ���Ե� Ư��
		NULL);					//������� ������ ���Ե� Ư�� �� Ȯ�� Ư���� ���� ������ ������ �ִ� ���ø� ���� �ڵ�

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
