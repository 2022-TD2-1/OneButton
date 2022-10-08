#include "PlayerBullet.h"

void PlayerBullet::Update()
{
	position += velocity;
	UpdateMatrix();
}

void PlayerBullet::Draw()
{
	Object3D::Draw();
}
