#ifndef _VEC2I_H_
#define _VEC2I_H_

#include <math.h>

struct Vec2i
{
	int x, y = 0.f;

	Vec2i(int x = 0.f, int y = 0.f) {
		this->x = x; this->y = y;
	}
	Vec2i(const Vec2i& vec) {
		this->x = vec.x; this->y = vec.y;
	}
	int SquaredLength() {
		return x * x + y * y;
	}
	float Length() {
		return sqrt(SquaredLength());
	}
	Vec2i Normalize() {
		return Vec2i(x, y) / Length();
	}
	Vec2i operator + (const Vec2i& vec) {
		return Vec2i(x + vec.x, y + vec.y);
	}
	Vec2i operator - (const Vec2i& vec) {
		return Vec2i(x - vec.x, y - vec.y);
	}
	Vec2i operator * (const int f) {
		return Vec2i(this->x * f, this->y * f);
	}
	Vec2i operator / (const int f) {
		return Vec2i(this->x / f, this->y / f);
	}


	Vec2i operator += (const Vec2i& vec) {
		x += vec.x; y += vec.y;
		return *this;
	}
	Vec2i operator -= (const Vec2i& vec) {
		x -= vec.x; y -= vec.y;
		return *this;
	}
	Vec2i operator *= (const Vec2i& vec) {
		x *= vec.x; y *= vec.y;
		return *this;
	}
	Vec2i operator /= (const Vec2i& vec) {
		x /= vec.x; y /= vec.y;
		return *this;
	}

	Vec2i operator *= (const int f) {
		x *= f; y *= f;
		return *this;
	}
};
#endif // _VEC2_H_

