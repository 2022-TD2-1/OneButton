#pragma once
#include <Object3D.h>
class TraceEffect
{
public:
public:
	void Ini(Vec3 pos,Vec3 moveSpd);

	void Update();
	void Draw();
	bool GetDead() { return isDead; }
private:
	Object3D obj;

	Vec3 sclSpeed;
	
	Vec3 moveSpd_;

	bool isDead = false;
};

