#pragma once
#include "IBossAttack.h"
#include "ModelManager.h"
#include "CircleCollider.h"

class BossBullet:
	public IBossAttack, public Object3D
{
public:
	BossBullet(Vec3 velocity) :velocity(velocity) { Object3D::Object3D(); this->model = ModelManager::Get("Sphere"); this->scale = Float3{ 0.3f, 0.3f, 0.3f}; }

	Vec3 velocity;

	const int MaxDeathCoolTime = 640;
	int deathCoolTime = MaxDeathCoolTime;

	CircleCollider col;

	void Update();
	void Draw();

};

