#pragma once
#include "Object3D.h"
#include "Parameters.h"
#include <PlayerOption.h>
#include <ModelManager.h>
#include "TraceEffect.h"
#include "PlayerHP.h"

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

    //HP�n
    void Damage(int damage);
    static const int maxhealth = 3;
    int health = 3;
    const int maxCoolTime = 80;
    int coolTime = 0;
    list<PlayerHP> hps_;    //hp�I�u�W�F
    Float4 color_;
    

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

    CircleCollider col;

    void UpdateCollisionPos();

    list<PlayerOption> opti;
private:
    static unique_ptr<Player> current;

    std::list<unique_ptr<TraceEffect>> trsEffect_;
};

