#include "BossCrossLaser.h"

void BossCrossLaser::Update()
{
	laser[0].Update();
	laser[1].Update();
}

void BossCrossLaser::Draw()
{
	laser[0].Draw();
	laser[1].Draw();
}
