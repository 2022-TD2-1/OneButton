#include "BossLaser.h"
#include "Easing.h"
#include <ApUtil.h>
#include <Parameters.h>
#include <Player.h>

void BossLaser::Update()
{
	timer.Update();

	if (timer.Check() > totalTime)
	{
		this->del = true;
		return;
	}

	if (timer.Check() > readyTime)
	{
		centerRad = defRad + (timer.Check()) * BossParams::laserSpeed;
		this->rotation.z = centerRad;
		*this->brightnessCB.contents = { 1.0f, 0.3f, 0.3f, 1.0f };

		UpdateCollisionPos();
		CheckCol();
	}
	else
	{
		centerRad = defRad + (timer.Check()) * BossParams::laserSpeed;
		this->rotation.z = centerRad;
		*this->brightnessCB.contents = { 1.0f, 0.3f, 0.3f, 1.0f };
		float flashyTime = sin(timer.Check() / 80);

		float flashyNum = cos(timer.Check() / 80);

		*this->brightnessCB.contents = {1.0f, flashyNum, flashyNum, 0.5f};
	}
	UpdateMatrix();
}

void BossLaser::Draw()
{
	Object3D::Draw("white");
}

void BossLaser::UpdateCollisionPos()
{
	col[0].x = ApUtil::ConvertRadDistToX(PlayerParams::circleR, centerRad);
	col[0].y = ApUtil::ConvertRadDistToY(PlayerParams::circleR, centerRad);
	col[0].r = 0.5f;

	col[1].x = ApUtil::ConvertRadDistToX(-PlayerParams::circleR, centerRad);
	col[1].y = ApUtil::ConvertRadDistToY(-PlayerParams::circleR, centerRad);
	col[1].r = 0.5f;
}

void BossLaser::CheckCol()
{
	for (auto c : col)
	{
		if (c.Collide(Player::GetCurrent()->col))
		{
			//プレイヤーと当たっていた時
			Player::GetCurrent()->Damage(this->laserDamage);
		}
	}
}
