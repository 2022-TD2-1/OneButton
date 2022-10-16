#pragma once
#include "Essentials.h"
#include <ICollider.h>
class IBossAttack
{
public:
	ICollider col;

	virtual void Update() = 0;
	virtual void Draw() = 0;

	bool del = false;
};

