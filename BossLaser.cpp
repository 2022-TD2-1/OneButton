#include "BossLaser.h"
#include "Easing.h"

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
		this->rotation.z = centerRad;
		*this->brightnessCB.contents = { 1.0f, 0.3f, 0.3f, 1.0f };
	}
	else
	{
		float flashyTime = timer.Check() > readyTime / 2 ?
			readyTime - timer.Check() :
			timer.Check();

		float flashyNum = timer.Check() <= readyTime / 2 ?
			EaseInQuint(flashyTime * 2 / readyTime) :
			EaseOutQuint(flashyTime * 2 / readyTime);

		*this->brightnessCB.contents = {1.0f, flashyNum, flashyNum, 0.5f};
	}
	UpdateMatrix();
}

void BossLaser::Draw()
{
	Object3D::Draw("white");
}
