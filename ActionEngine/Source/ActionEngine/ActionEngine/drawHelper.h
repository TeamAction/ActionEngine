#pragma once

struct v2
{
	inline v2(float _x =0, float _y=0) : x(_x), y(_y) {}
	float x, y;
};
inline v2 operator+(v2 a, v2 b)
{
	return v2(a.x + b.x, a.y+ b.y);
}

inline v2 operator*(v2 a, float b)
{
	return v2(a.x *b, a.y *b);
}

struct drawObject
{
	inline drawObject(int _index, v2 _position = v2()): spriteIndex(_index), screenPosition(_position) {}
	int spriteIndex;
	v2 screenPosition;
};