#pragma once
#include "Object3D.h"
#include "Parameters.h"
class Player :
    public Object3D
{
public:
    Player() { Object3D::Object3D(); };

    void Update();
    void Draw();
    
    int attackTimer = PlayerParams::attackTime[0];
};

