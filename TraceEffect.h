#pragma once
#include <Object3D.h>
class TraceEffect
{
public:
public:
	void Ini(Vec3 pos);

	void Update();
	void Draw();
	bool GetDead() { return isDead; }
private:
	Object3D obj;

	Vec3 sclSpeed;
	


	bool isDead = false;
};

