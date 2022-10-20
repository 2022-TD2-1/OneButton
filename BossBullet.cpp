#include "BossBullet.h"
#include <Player.h>

void BossBullet::Update()
{
	deathCoolTime--;
	if (deathCoolTime <= 0) {
		this->del = true;
	}


	position += velocity;
	UpdateMatrix();

	//当たり判定の座標更新
	col.x = this->position.x;
	col.y = this->position.y;
	col.r = this->scale.x;

	//当たっていたらダメージ
	if (col.Collide(Player::GetCurrent()->col))
	{
		Player::GetCurrent()->Damage(1);
	}
}

void BossBullet::Draw()
{
	Object3D::Draw();
}
