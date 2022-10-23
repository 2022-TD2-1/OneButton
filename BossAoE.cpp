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
		//—\‰~
		*this->brightnessCB.contents = { 1.f, 1.f, 1.f, .25f };
	}
	else 
	{
		//UŒ‚
		*this->brightnessCB.contents = { 1.f, 1.f, 1.f, 1.f };
		if (col.Collide(Player::GetCurrent()->col))
		{
			Player::GetCurrent()->Damage(1);
		}
	}

	col.r = PlayerParams::circleR * 3 / 4;

	col.x = position.x;
	col.y = position.y;

	scale = { col.r, col.r, col.r };
	UpdateMatrix();
}

void BossAoE::Draw()
{
	Object3D::Draw();
}
