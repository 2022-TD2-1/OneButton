#pragma once

struct Float3;
class Vec2;

class Vec3
{
public:
	float x;
	float y;
	float z;

	Vec3();
	Vec3(float x, float y, float z);

	//Sqrtが呼ばれる
	Vec3& SetLength(float l);

	Vec3 operator+(const Vec3& v2) const;

	Vec3 operator-(const Vec3& v2) const;
	Vec3 operator-() const;

	Vec3 operator*(float mul) const;

	Vec3 operator/(float div) const;

	Vec3& operator +=(const Vec3& v2);

	Vec3& operator -=(const Vec3& v2);

	Vec3& operator *=(float mul);

	Vec3& operator /=(float div);

	bool operator > (const Vec3& v2) const;
	bool operator >= (const Vec3& v2) const;
	bool operator < (const Vec3& v2) const;
	bool operator <= (const Vec3& v2) const;

	//Sqrtが呼ばれる
	Vec3& Norm();
	//Sqrtが呼ばれない。長さがわかっている場合に。
	Vec3& Norm(float length);

	//Sqrtが呼ばれる
	Vec3 GetNorm() const;
	//Sqrtが呼ばれない。長さがわかっている場合に。
	Vec3 GetNorm(float length) const;

	float GetLength() const;

	float GetSquaredLength() const;

	float Dot(const Vec3& v2) const;
	Vec3 Cross(const Vec3& v2) const;

	static Vec3 Lerp(const Vec3& start, const Vec3& end, const float t);
	//t 経過時間    b最初の位置    c移動量    d移動時間
	static float easeOutBack(float t, float b, float c, float d);
	static float easeInOutBack(float t, float b, float c, float d);

	operator Float3() const;
	operator Vec2() const;
};

