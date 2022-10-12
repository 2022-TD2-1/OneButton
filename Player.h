#pragma once
#include "Object3D.h"
#include "Parameters.h"
#include <PlayerBullet.h>
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
    
    int attackTimer = PlayerParams::attackTime[0];

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
private:
    PlayerOption opti = PlayerOption();

    static unique_ptr<Player> current;

    //弾関連
private:
    vector<PlayerBullet> bullets;

    void UpdateAllBullets();
    void DrawAllBullets();
};

