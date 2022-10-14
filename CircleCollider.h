#pragma once
#include "ICollider.h"
class CircleCollider : public ICollider
{
public:
	float x, y, r;

	bool Collide(CircleCollider other);
};

