#pragma once
#include "Object3D.h"
#include <PlayerOption.h>
class Boss :
    public Object3D
{
public:
    Boss(){};

    void Init();

    void Update();
    void Draw();

    void Hit(PlayerOption* other);

    int health = 10000;

    enum class State {
        Center,
        Down
    } state = State::Center;

    void CenterUpdate();
    void DownUpdate();

    void UpdateCol();

    void MoveTo(Vec3 goal, float speed);

    CircleCollider col;

private:
    static unique_ptr<Boss> current;

public:
    static Boss* Create();
    static Boss* GetCurrent();
};

