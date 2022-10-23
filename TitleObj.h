#pragma once
#include <CircleCollider.h>
#include "PlayerOption.h"
#include <Object3D.h>
class TitleObj : public Object3D
{
public:
	void Ini();
	void Update();
	void Draw();

	void Hit(PlayerOption* other);

private:

	CircleCollider col;
};

