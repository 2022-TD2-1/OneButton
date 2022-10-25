#include "BossAoE.h"
#include <Player.h>

void BossAoE::Update()
{
	timer.Update();

	if (timer.Check() > totalTime)
	{
		del = true;
		return;
	}

	if (timer.Check() < readyTime)
	{
		//ó\çêâ~
		*this->brightnessCB.contents = { 1.f, 1.f, 1.f, .1f };
		//çUåÇ
		*entityObj.brightnessCB.contents = { 1.f, 1.f, 1.f, 1.f };

	}
	else 
	{
		if (entityObj.scale.x < PlayerParams::circleR * 3 / 4) {
			entityObj.scale += {0.05f, 0.05f, 0.05f};
		}

		if (col.Collide(Player::GetCurrent()->col))
		{
			Player::GetCurrent()->Damage(1);
		}
	}

	

	col.r = entityObj.scale.x;

	col.x = position.x;
	col.y = position.y;

	scale = { 
		PlayerParams::circleR * 3 / 4,
		PlayerParams::circleR * 3 / 4,
		PlayerParams::circleR * 3 / 4 };

	entityObj.UpdateMatrix();
	UpdateMatrix();
}

void BossAoE::Draw()
{
	entityObj.Draw();
	Object3D::Draw();
}
