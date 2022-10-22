#pragma once
#include <Object3D.h>
#include <Vec3.h>
#include <ModelManager.h>
#include <CircleCollider.h>
class PlayerBullet
	: public Object3D
{
public:
	PlayerBullet(Vec3 vel);

	Vec3 vel;

	void Update();
	void Draw();

	int timer = 180;
	bool del = false;

	CircleCollider col;
};

