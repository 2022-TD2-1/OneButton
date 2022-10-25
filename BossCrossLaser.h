#pragma once
#include "IBossAttack.h"
#include <BossLaser.h>
class BossCrossLaser :
    public IBossAttack
{
public:
    BossCrossLaser(float rad) {
        laser->emplace_back(rad);
        laser->emplace_back(rad + PIf / 2);
    };
    void Update() override;
    void Draw() override;

   vector<BossLaser> laser[2];
};