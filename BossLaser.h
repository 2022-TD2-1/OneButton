#pragma once
#include "IBossAttack.h"
#include <Timer.h>
#include <ModelManager.h>
#include <CircleCollider.h>
class BossLaser :
    public IBossAttack, public Object3D
{
public:
    BossLaser(float centerRad) :defRad(centerRad) {
        timer.Start(); 
        model = ModelManager::Get("Cube");
        this->scale.x = length*2;
    };

    void Update() override;
    void Draw() override;
    float defRad;

    float centerRad;

    Timer timer;

    const int readyTime = 1000;
    static const int totalTime = 4000;

    float length = 8.0f;

    CircleCollider col[2];

    //“–‚½‚è”»’è‚ÌˆÊ’u‚ğXV
    void UpdateCollisionPos();
    //UŒ‚‚Ì“–‚½‚è”»’è‚ğŒ©‚é
    void CheckCol();
    const int laserDamage = 1;
};

