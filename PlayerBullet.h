#pragma once
#include "Object3D.h"
class PlayerBullet:
	public Object3D
{
public:
	PlayerBullet(Vec3 velocity):velocity(velocity) { Object3D::Object3D(); }

	Vec3 velocity;

	void Update();
	void Draw();

	//�폜����Ȃ�true
	bool del = false;
};

