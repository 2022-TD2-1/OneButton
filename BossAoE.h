#pragma once
#include "IBossAttack.h"
#include "CircleCollider.h"
#include <Parameters.h>
#include <ApUtil.h>
#include <Timer.h>
#include <ModelManager.h>
class BossAoE :
    public IBossAttack, public Object3D
{
public:
    BossAoE(float rad) {
        this->model = ModelManager::Get("Bullet");
        col.r = PlayerParams::circleR * 3 / 4;
        position.x = ApUtil::ConvertRadDistToX(posR, rad);
        position.y = ApUtil::ConvertRadDistToY(posR, rad);

        col.x = position.x;
        col.y = position.y;

        scale = { col.r, col.r, col.r };

        UpdateMatrix();

        this->timer.Start();

        entityObj.model = model;
        entityObj.position = position;
        entityObj.scale = {0,0,0};
        entityObj.UpdateMatrix();
    };

    void Update();
    void Draw();

    CircleCollider col;
    float posR = (float)PlayerParams::circleR * 3 / 4;

    Timer timer;
    double readyTime = 2000.0l;
    const static int totalTime = 5000;

    Object3D entityObj;
};

