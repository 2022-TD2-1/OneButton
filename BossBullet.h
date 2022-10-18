#pragma once
#include "IBossAttack.h"
#include "ModelManager.h"

class BossBullet:
	public IBossAttack, public Object3D
{
public:
	BossBullet(Vec3 velocity) :velocity(velocity) { Object3D::Object3D(); this->model = ModelManager::Get("Sphere"); this->scale = Float3{ 0.3f, 0.3f, 0.3f}; }

	Vec3 velocity;

	void Update();
	void Draw();

	//íœ‚·‚é‚È‚çtrue
	bool del = false;
};

