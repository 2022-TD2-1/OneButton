#include "BossCrossLaser.h"

void BossCrossLaser::Update()
{
	laser->front().Update();
	laser->back().Update();
}

void BossCrossLaser::Draw()
{
	laser->front().Draw();
	laser->back().Draw();
}
