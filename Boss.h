#pragma once
#include "Object3D.h"
#include <PlayerOption.h>
#include <IBossAttack.h>
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

    enum class AttackType {
        Idle,
        Bullets,
        Bar1,
        Bar2,
        AoE,
    };

    //ダウン、非ダウンの処理
    void CenterUpdate();
    void DownUpdate();

    //フェーズごとの攻撃パターン処理
    void P1Update();
    void P2Update();
    void P3Update();

    //攻撃ごとの処理
    void IdleUpdate();
    void BulletsUpdate();
    void Bar1Update();
    void Bar2Update();
    void AoEUpdate();

    //攻撃のアップデートとドロー
    void UpdateAllAttacks();
    void DrawAllAttacks();

    void UpdateCol();

    void MoveTo(Vec3 goal, float speed);

    CircleCollider col;

    list<unique_ptr<IBossAttack>> bossAttacks;
private:
    static unique_ptr<Boss> current;

public:
    static Boss* Create();
    static Boss* GetCurrent();
};

