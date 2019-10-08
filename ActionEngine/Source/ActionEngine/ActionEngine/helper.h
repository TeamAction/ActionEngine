#pragma once

struct v2 {
	v2(float x, float y)
	{
		v[0] = x;
		v[1] = y;
	}
	float v[2];
};

struct drawObject
{
	int spriteIndex;
	v2 screenPosition;
};
