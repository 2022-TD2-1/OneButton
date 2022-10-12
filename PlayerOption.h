#pragma once
#include "Object3D.h"
class PlayerOption :
    public Object3D
{
public:
    PlayerOption() { Object3D::Object3D(); };

    void Update();
    void Draw();

    float x = 0;
    //TODO: Params�ŏ����l�Ƒ����ʂ�ݒ肷��
    float speed = 0;
    enum class Side {
        Clock,
        CounterClock
    } facing = Side::Clock;

    enum class State {
        Move,
        Attack,
        Back
    } state = State::Attack;

    void MoveUpdate();
    void AttackUpdate();
    void BackUpdate();
};

