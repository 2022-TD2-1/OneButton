#pragma once
#include "Object3D.h"
#include "Parameters.h"
#include <PlayerBullet.h>

enum class Side {
    Clock,
    CounterClock
};

class Player :
    public Object3D
{
public:
    Player() { Object3D::Object3D(); };

    void Update();
    void Draw();
    
    int attackTimer = PlayerParams::attackTime[0];

    int x = 0;
    Side facing = Side::Clock;

    enum class State {
        Move,
        Stop
    } state = State::Move;

    //現在のプレイヤーのインスタンスを取得
    static Player* GetCurrent();

    //プレイヤーを初期化してCurrentに設定
    static Player* Create();
private:

    static unique_ptr<Player> current;

    //弾関連
private:
    vector<PlayerBullet> bullets;

    void UpdateAllBullets();
    void DrawAllBullets();
};

