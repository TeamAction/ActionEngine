#pragma once

struct v2 
{
	v2(float _x =0, float _y=0) : x(_x), y(_y) {}
	float x, y;
	v2 operator+(const v2& other)
	{
		return v2(x + other.x, y + other.y);
	}
	v2 operator*(const float& other)
	{
		return v2(x * other, y * other);
	}
};

struct drawObject
{
	drawObject(int _index = 0, v2 _position = v2()): spriteIndex(_index), screenPosition(_position) {}
	int spriteIndex;
	v2 screenPosition;
};

struct Sprite
{
	Sprite(int _index = 0,v2 _position = v2(),v2 _size = v2()) : index(_index), positionOnSheet(_position), sizeOnSheet(_size){}
	int index;
	v2 positionOnSheet;
	v2 sizeOnSheet;
};
