#include "BossBullet.h"

void BossBullet::Update()
{
	deathCoolTime--;
	if (deathCoolTime <= 0) {
		this->del = true;
	}


	position += velocity;
	UpdateMatrix();
}

void BossBullet::Draw()
{
	Object3D::Draw();
}
