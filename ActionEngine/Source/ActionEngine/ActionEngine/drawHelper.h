#pragma once

struct v2
{
	inline v2(float _x =.0f, float _y=.0f) : x(_x), y(_y) {}
	float x, y;
};
inline v2 operator+(v2 a, v2 b)
{
	return v2(a.x + b.x, a.y+ b.y);
}

inline v2 operator-(v2 a, v2 b)
{
	return v2(a.x - b.x, a.y - b.y);
}

inline float dot(v2 a, v2 b)
{
	return(a.x * b.x + a.y * b.y);
}

inline v2 operator*(v2 a, float b)
{
	return v2(a.x *b, a.y *b);
}

inline v2 operator*(float b,v2 a)
{
	return v2(a.x *b, a.y *b);
}

inline v2 operator/(v2 a, float b)
{
	return v2(a.x /b, a.y /b);
}
inline v2 operator/(float b,v2 a)
{
	return v2(a.x /b, a.y /b);
}
inline v2 operator*(v2 a, v2 b)
{
	return v2(a.x *b.x, a.y *b.y);
}

struct drawObject
{
	inline drawObject(int _index, v2 _position = v2(),v2 _scale = v2()): spriteIndex(_index), screenPosition(_position), screenScale(_scale) {}
	int spriteIndex;
	v2 screenPosition;
	v2 screenScale;
};

struct AABB
{
	v2 bLeft;
	v2 tRight;
};



struct mat3x3
{
	float mat[3][3] = { {1,0,0},{0,1,0},{0,0,1}};
};

inline mat3x3 operator*(mat3x3 a,mat3x3 b)
{
	mat3x3 product;
	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
		{
			float sum = 0;
			for (int z = 0; z < 3; ++z)
				sum += a.mat[x][z] * b.mat[z][y];
			product.mat[x][y] = sum;
		}
	return product;
}


inline void Translate(mat3x3 a,float xTrans, float yTrans)
{
	mat3x3 b;
	b.mat[0][0] = 1;    b.mat[0][1] = 0;    b.mat[0][2] = 0;
	b.mat[1][0] = 0;    b.mat[1][1] = 1;    b.mat[1][2] = 0;
	b.mat[2][0] = xTrans; b.mat[2][1] = yTrans; b.mat[2][2] = 1;
	a = a * b;
}

inline void Scale(mat3x3 a, float xScale, float yScale)
{
	mat3x3 b;
	b.mat[0][0] = xScale; b.mat[0][1] = 0;   b.mat[0][2] = 0;
	b.mat[1][0] = 0;   b.mat[1][1] = yScale; b.mat[1][2] = 0;
	b.mat[2][0] = 0;   b.mat[2][1] = 0;   b.mat[2][2] = 1;
	a = a * b;
}

inline void Rotate(mat3x3 a, float degrees)
{
	mat3x3 b;
	if (degrees == 0) return;
	float radians = 6.283185308 / (360.0 / degrees);
	float c = cos(radians);
	float s = sin(radians);
	b.mat[0][0] = c; b.mat[0][1] = s; b.mat[0][2] = 0;
	b.mat[1][0] = -s; b.mat[1][1] = c; b.mat[1][2] = 0;
	b.mat[2][0] = 0; b.mat[2][1] = 0; b.mat[2][2] = 1;
	a = a * b;
}
