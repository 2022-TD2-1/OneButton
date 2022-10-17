#pragma once
#include "IBossAttack.h"
#include <Timer.h>
#include <ModelManager.h>
class BossLaser :
    public IBossAttack
{
    BossLaser(float centerRad) :centerRad(centerRad) { timer.Start(); model = ModelManager::Get("Cube"); };

    void Update() override;
    void Draw() override;

    float centerRad;

    Timer timer;

    const int readyTime = 1000;
    const int totalTime = 4000;
};

