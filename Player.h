#pragma once
#include "Object3D.h"
#include "Parameters.h"
#include <PlayerOption.h>
#include <ModelManager.h>
#include "TraceEffect.h"

class Player :
    public Object3D
{
public:
    Player() { 
        Object3D::Object3D();
    };

    void Init();

    void Update();
    void Draw();

    float x = 0.f;
    enum class Side {
        Clock,
        CounterClock
    } facing = Side::Clock;

    enum class State {
        Move,
        Stop
    } state = State::Move;

    //���݂̃v���C���[�̃C���X�^���X���擾
    static Player* GetCurrent();

    //�v���C���[������������Current�ɐݒ�
    static Player* Create();

    PlayerOption opti = PlayerOption();
private:

    static unique_ptr<Player> current;

    std::list< std::unique_ptr<TraceEffect>> traEffect_;
};

