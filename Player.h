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

    //HP系
    void Damage(int damage);
    static const int maxhealth = 3;
    int health = 3;
    const int maxCoolTime = 80;
    int coolTime = 0;
    list<PlayerHP> hps_;    //hpオブジェ
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

    //現在のプレイヤーのインスタンスを取得
    static Player* GetCurrent();

    //プレイヤーを初期化してCurrentに設定
    static Player* Create();

    CircleCollider col;

    void UpdateCollisionPos();

    list<PlayerOption> opti;
private:
    static unique_ptr<Player> current;

    std::list<unique_ptr<TraceEffect>> trsEffect_;
};

