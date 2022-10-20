#pragma once
#include "ICollider.h"
class CircleCollider : public ICollider
{
public:
	CircleCollider() {};
	CircleCollider(float x, float y, float r) : x(x), y(y), r(r){};

	float x, y, r;

	bool Collide(CircleCollider other);
};

