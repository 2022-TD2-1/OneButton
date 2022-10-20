#pragma once
#include "Object3D.h"
#include "Parameters.h"
#include <PlayerOption.h>
#include <ModelManager.h>

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
    int health = 5000;

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

    PlayerOption opti = PlayerOption();
private:

    static unique_ptr<Player> current;
};

