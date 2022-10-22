#include "Vec3.h"
#include "Vec2.h"
#include <math.h>
#include "Float3.h"

Vec3::Vec3() :x(0), y(0), z(0)
{
}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vec3& Vec3::SetLength(float l)
{
	float len2 = this->GetLength();
	float mul = l / len2;
	x *= mul;
	y *= mul;
	z *= mul;

	return *this;
}

Vec3 Vec3::operator+(const Vec3& v2) const
{
	return Vec3(this->x + v2.x, this->y + v2.y, this->z + v2.z);
}

Vec3 Vec3::operator-(const Vec3& v2) const
{
	return Vec3(this->x - v2.x, this->y - v2.y, this->z - v2.z);
}

Vec3 Vec3::operator-() const
{
	return Vec3(-this->x, -this->y, -this->z);
}

Vec3 Vec3::operator*(float mul) const
{
	return Vec3(this->x * mul, this->y * mul, this->z * mul);
}

Vec3 Vec3::operator/(float div) const
{
	return Vec3(this->x / div, this->y / div, this->z / div);
}

Vec3& Vec3::operator+=(const Vec3& v2)
{
	this->x += v2.x;
	this->y += v2.y;
	this->z += v2.z;

	return *this;
}

Vec3& Vec3::operator-=(const Vec3& v2)
{
	this->x -= v2.x;
	this->y -= v2.y;
	this->z -= v2.z;

	return *this;
}

Vec3& Vec3::operator*=(float mul)
{
	this->x *= mul;
	this->y *= mul;
	this->z *= mul;

	return *this;
}

Vec3& Vec3::operator/=(float div)
{
	this->x /= div;
	this->y /= div;
	this->z /= div;

	return *this;
}

bool Vec3::operator>(const Vec3& v2) const
{
	return this->GetSquaredLength() > v2.GetSquaredLength();
}

bool Vec3::operator>=(const Vec3& v2) const
{
	return this->GetSquaredLength() >= v2.GetSquaredLength();
}

bool Vec3::operator<(const Vec3& v2) const
{
	return this->GetSquaredLength() < v2.GetSquaredLength();
}

bool Vec3::operator<=(const Vec3& v2) const
{
	return this->GetSquaredLength() <= v2.GetSquaredLength();
}

Vec3& Vec3::Norm()
{
	float l = this->GetLength();
	if (l) {
		this->x /= l;
		this->y /= l;
		this->z /= l;
	}
	else {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	return *this;
}

Vec3& Vec3::Norm(float length)
{
	const float& l = length;
	if (l) {
		this->x /= l;
		this->y /= l;
		this->z /= l;
	}
	else {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	return *this;
}

Vec3 Vec3::GetNorm() const
{
	float l = this->GetLength();
	if (l)
		return Vec3(this->x / l, this->y / l, this->z / l);
	else
		return Vec3();
}

Vec3 Vec3::GetNorm(float length) const
{
	const float& l = length;
	if (l)
		return Vec3(this->x / l, this->y / l, this->z / l);
	else
		return Vec3();
}

float Vec3::GetLength() const
{
	return sqrtf(this->GetSquaredLength());
}

float Vec3::GetSquaredLength() const
{
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

float Vec3::Dot(const Vec3& v2) const
{
	return x*v2.x + y*v2.y + z*v2.z;
}

Vec3 Vec3::Cross(const Vec3& v2) const
{
	return Vec3(y*v2.z - z*v2.y, z*v2.x - x*v2.z, x*v2.y - y*v2.x);
}

Vec3 Vec3::Lerp(const Vec3& start, const Vec3& end, const float t)
{
	Vec3 diff = end - start;
	return start + diff * t;
}

float Vec3::easeOutBack(float t, float b, float c, float d)
{
	return c * ((t = t / d - 1) * t * t * t * t + 1) + b;
}

float Vec3::easeInOutBack(float t, float b, float c, float d)
{
	float s = 1.70158f;
	if ((t /= d / 2) < 1) return c / 2 * (t * t * (((s *= (1.525f)) + 1) * t - s)) + b;
	float postFix = t -= 2;
	return c / 2 * ((postFix)*t * (((s *= (1.525f)) + 1) * t + s) + 2) + b;
}

Vec3::operator Float3() const
{
	return Float3{ x, y, z };
}

Vec3::operator Vec2() const
{
	return Vec2(x, y);
}