#include "PlayerBullet.h"
#include <Player.h>
#include <Boss.h>

void PlayerBullet::Update()
{
	this->position = vel + this->position;
	col.x = position.x;
	col.y = position.y;
	col.r = 0.3;
	this->scale = { col.r, col.r, col.r };
	timer--;
	if (timer < 0)
	{
		del = true;
	}
	this->UpdateMatrix();

	if(col.Collide(Boss::GetCurrent()->col))
	{
		this->del = true;
		Boss::GetCurrent()->Hit();
	}
}

void PlayerBullet::Draw()
{
	(*brightnessCB.contents) = Float4{ 0.5f, 1.0f, 1.0f, 1.0f };
	Object3D::Draw("white");
}

PlayerBullet::PlayerBullet(Vec3 vel) : vel(vel) {
	this->model = ModelManager::Get("Sphere");
	this->position = Player::GetCurrent()->position;
	col.x = position.x;
	col.y = position.y;
	col.r = 0.3;
	this->UpdateMatrix();
};
