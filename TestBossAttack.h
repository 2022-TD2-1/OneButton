#pragma once
#include "IBossAttack.h"
#include <CircleCollider.h>
class TestBossAttack :
    public IBossAttack
{
    CircleCollider col;
};

