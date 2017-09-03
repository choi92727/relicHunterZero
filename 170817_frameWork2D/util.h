#pragma once

//angle * DEG_TO_RAD
#define DEG_TO_RAD 0.017435 //디그리 1도(라디안값)
#define PI 3.14159265358979

#define PI2 PI * 2

#define PI_2 PI / 2
#define PI_4 PI / 4
#define PI_8 PI / 8
#define PI_16 PI / 16
#define PI_32 PI / 32

namespace MY_UTIL
{
	float getAngle(float startX, float startY, float endX, float endY);
	float newGetAngle(float startX, float startY, float endX, float endY);
	float getDistance(float startX, float startY, float endX, float endY);
}