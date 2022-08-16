#ifndef _VEC2F_H_
#define _VEC2F_H_

#include <math.h>

struct Vec2f
{
	float x, y = 0.f;

	Vec2f(float x = 0.f, float y = 0.f) {
		this->x = x; this->y = y;
	}
	Vec2f(const Vec2f& vec) {
		this->x = vec.x; this->y = vec.y;
	}
	float SquaredLength() {
		return x * x + y * y;
	}
	float Length() {
		return sqrt(SquaredLength());
	}
	Vec2f Normalize() {
		return Vec2f(x, y) / Length();
	}
	Vec2f operator + (const Vec2f& vec) {
		return Vec2f(x + vec.x, y + vec.y);
	}
	Vec2f operator - (const Vec2f& vec) {
		return Vec2f(x - vec.x, y - vec.y);
	}
	Vec2f operator * (const float f) {
		return Vec2f(this->x * f, this->y * f);
	}
	Vec2f operator / (const float f) {
		return Vec2f(this->x / f, this->y / f);
	}


	Vec2f operator += (const Vec2f& vec) {
		x += vec.x; y += vec.y;
		return *this;
	}
	Vec2f operator -= (const Vec2f& vec) {
		x -= vec.x; y -= vec.y;
		return *this;
	}
	Vec2f operator *= (const Vec2f& vec) {
		x *= vec.x; y *= vec.y;
		return *this;
	}
	Vec2f operator /= (const Vec2f& vec) {
		x /= vec.x; y /= vec.y;
		return *this;
	}

	Vec2f operator *= (const float f) {
		x *= f; y *= f;
		return *this;
	}
};
#endif // _VEC2_H_
