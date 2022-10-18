#pragma once
#include "IBossAttack.h"
#include <BossLaser.h>
class BossCrossLaser :
    public IBossAttack
{
public:
    void Update() override;
    void Draw() override;

    BossLaser laser[2];
};