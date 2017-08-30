#include "stdafx.h"
#include "util.h"

namespace MY_UTIL
{
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		float distance = sqrtf(x * x + y * y);
		float angle = x / distance;

		if (endY > startY)
		{
			angle = -angle;

			if (angle >= PI2) angle -= PI2;
		}

		return angle;
	}

	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}
}