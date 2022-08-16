#ifndef _VEC3F_H_
#define _VEC3F_H_

#include <math.h>
struct Vec3f
{
	float x, y, z = 0.f;

	Vec3f(float x = 0.f, float y = 0.f, float z = 0.f) {
		this->x = x; this->y = y; this->z = z;
	}
	Vec3f(const Vec3f& vec) {
		this->x = vec.x; this->y = vec.y; this->z = vec.z;
	}

	Vec3f xy() {
		return Vec3f(x, y, 0.f);
	}
	Vec3f yz() {
		return Vec3f(0.f, y, z);
	}
	Vec3f xz() {
		return Vec3f(x, 0.f, z);
	}

	static Vec3f Identity() {
		return Vec3f(1.f, 1.f, 1.f);
	}

	float SquaredLength() {
		return x * x + y * y + z * z;
	}
	float Length() {
		return sqrt(SquaredLength());
	}
	Vec3f Normalize() {
		return Vec3f(x, y, z) / Length();
	}
	Vec3f operator + (const Vec3f& vec) {
		return Vec3f(x + vec.x, y + vec.y, z + vec.z);
	}
	
	Vec3f operator - (const Vec3f& vec) {
		return Vec3f(x - vec.x, y - vec.y, z - vec.z);
	}
	Vec3f operator * (const float f) {
		return Vec3f(this->x * f, this->y * f, this->z * f);
	}
	Vec3f operator / (const float f) {
		return Vec3f(this->x / f, this->y / f, this->z / f);
	}


	Vec3f operator += (const Vec3f& vec) {
		x += vec.x; y += vec.y; z += vec.z;
		return *this;
	}
	Vec3f operator -= (const Vec3f& vec) {
		x -= vec.x; y -= vec.y; z -= vec.z;
		return *this;
	}
	Vec3f operator *= (const Vec3f& vec) {
		x *= vec.x; y *= vec.y; z *= vec.z;
		return *this;
	}
	Vec3f operator /= (const Vec3f& vec) {
		x /= vec.x; y /= vec.y; z /= vec.z;
		return *this;
	}

	Vec3f operator *= (const float f) {
		x *= f; y *= f; z *= f;
		return *this;
	}
};

#endif
