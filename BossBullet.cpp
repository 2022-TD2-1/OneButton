#include "BossBullet.h"

void BossBullet::Update()
{
	position += velocity;
	UpdateMatrix();
}

void BossBullet::Draw()
{
	Object3D::Draw();
}
