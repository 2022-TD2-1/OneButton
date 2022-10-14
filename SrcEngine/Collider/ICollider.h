#pragma once
class ICollider
{
public:
	bool Collide(const ICollider& other) { return false; };
};
