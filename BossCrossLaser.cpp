#include "BossCrossLaser.h"

void BossCrossLaser::Update()
{
	laser->front().Update();
	laser->back().Update();

	if (laser->front().del)
	{
		this->del = true;
	}
}

void BossCrossLaser::Draw()
{
	laser->front().Draw();
	laser->back().Draw();
}
