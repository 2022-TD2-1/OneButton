#pragma once
#include "IBossAttack.h"
#include "ModelManager.h"
#include "CircleCollider.h"

class BossBullet:
	public IBossAttack, public Object3D
{
public:
	BossBullet(Vec3 velocity) :velocity(velocity) { 
		Object3D::Object3D(); 
		this->model = ModelManager::Get("Sphere");
		this->scale = Float3{ 0.7f, 0.7f, 0.7f}; 
	}

	Vec3 velocity;

	const int MaxDeathCoolTime = 640;
	int deathCoolTime = MaxDeathCoolTime;

	CircleCollider col;

	void Update();
	void Draw();

};

