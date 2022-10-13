#include "CircleCollider.h"
#include <Float2.h>

bool CircleCollider::Collide(CircleCollider other)
{
    Float2 diff = {
        x - other.x,
        y - other.y
    };

    float sumR = r + other.r;

    diff.x *= diff.x;
    diff.y *= diff.y;
    sumR *= sumR;
    return diff.x + diff.y <= sumR;
}
