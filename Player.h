#pragma once
#include "Object3D.h"
#include "Parameters.h"
#include <PlayerOption.h>
#include <ModelManager.h>
#include <PlayerBullet.h>
#include <Timer.h>

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
    int health = 5000;
    const int maxCoolTime = 80;
    int coolTime = 0;
    Float4 color_;
    Object3D hpObj[maxhealth];

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

private:
    void UpdateAllBullets();
    void DrawAllBullets();

    LimitedTimer bulletTimer = LimitedTimer((double)500.0f);
    float bulletSpeed = 0.08f;
    list<PlayerBullet> bullets;

    void RegisterBullet(Vec3 vel);
};

