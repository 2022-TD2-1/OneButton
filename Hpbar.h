#include <Object3D.h>
#pragma once
class Hpbar
{
public:

	void Ini(float maxHp, Vec3 pos);
	void Update(float nowHp);
	void Draw();

private:
	Object3D hpBar_;
	float MaxHP_;


};

