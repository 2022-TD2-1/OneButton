#include "BossLaser.h"

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
		centerRad = (timer.Check() - 1000) * PIf / 1800;
		*this->brightnessCB.contents = { 1.0f, 0.3f, 0.3f, 1.0f };
	}
	else
	{
		*this->brightnessCB.contents = {1.0f, 0.0f, 0.0f, 0.5f};
	}
}

void BossLaser::Draw()
{
	Object3D::Draw();
}
