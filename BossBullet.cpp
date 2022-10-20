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

	//�����蔻��̍��W�X�V
	col.x = this->position.x;
	col.y = this->position.y;
	col.r = this->scale.x;

	//�������Ă�����_���[�W
	if (col.Collide(Player::GetCurrent()->col))
	{
		Player::GetCurrent()->Damage(1);
	}
}

void BossBullet::Draw()
{
	Object3D::Draw();
}
