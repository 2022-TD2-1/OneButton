#pragma once
#include "Essentials.h"
#include <ICollider.h>
class IBossAttack
{
public:
	ICollider col;
};

static list<IBossAttack> bossAttacks;

