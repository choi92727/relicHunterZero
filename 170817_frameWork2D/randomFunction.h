#pragma once
#include "singletonBase.h"

class randomFunction : public singletonBase<randomFunction>
{
public:
	randomFunction() {};
	~randomFunction() {};

	int getInt(int num) { return rand() % num; }

	int getIntFromInto(int fromNum, int toNum) { return rand() % (toNum - fromNum + 1) + fromNum; }

	float getFloat(float num) { return (float)rand() / (float)RAND_MAX * num; }

	float getFloatFromInto(float fromNum, float toNum) { return (float)rand() / (float)RAND_MAX * (toNum - fromNum) + fromNum; }
};