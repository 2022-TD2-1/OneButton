#pragma once
#include "Essentials.h"
#include <ICollider.h>
#include <Object3D.h>
class IBossAttack : public Object3D
{
public:
	unique_ptr<ICollider> col;

	virtual void Update() = 0;
	virtual void Draw() = 0;

	bool del = false;
};

