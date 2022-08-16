#ifndef _VEC3I_H_
#define _VEC3I_H_

struct Vec3i
{
	int x, y, z = 0.f;

	Vec3i(int x = 0.f, int y = 0.f, int z = 0.f) {
		this->x = x; this->y = y; this->z = z;
	}
	Vec3i(const Vec3i& vec) {
		this->x = vec.x; this->y = vec.y; this->z = vec.z;
	}

	Vec3i xy() {
		return Vec3i(x, y, 0.f);
	}
	Vec3i yz() {
		return Vec3i(0.f, y, z);
	}
	Vec3i xz() {
		return Vec3i(x, 0.f, z);
	}

	int SquaredLength() {
		return x * x + y * y + z * z;
	}
	float Length() {
		return sqrt(SquaredLength());
	}
	Vec3i Normalize() {
		return Vec3i(x, y, z) / Length();
	}
	Vec3i operator + (const Vec3i& vec) {
		return Vec3i(x + vec.x, y + vec.y, z + vec.z);
	}
	Vec3i operator - (const Vec3i& vec) {
		return Vec3i(x - vec.x, y - vec.y, z - vec.z);
	}
	Vec3i operator * (const int f) {
		return Vec3i(this->x * f, this->y * f, this->z * f);
	}
	Vec3i operator / (const int f) {
		return Vec3i(this->x / f, this->y / f, this->z / f);
	}


	Vec3i operator += (const Vec3i& vec) {
		x += vec.x; y += vec.y; z += vec.z;
		return *this;
	}
	Vec3i operator -= (const Vec3i& vec) {
		x -= vec.x; y -= vec.y; z -= vec.z;
		return *this;
	}
	Vec3i operator *= (const Vec3i& vec) {
		x *= vec.x; y *= vec.y; z *= vec.z;
		return *this;
	}
	Vec3i operator /= (const Vec3i& vec) {
		x /= vec.x; y /= vec.y; z /= vec.z;
		return *this;
	}

	Vec3i operator *= (const int f) {
		x *= f; y *= f; z *= f;
		return *this;
	}
};
#endif // !_VEC3I_H_

