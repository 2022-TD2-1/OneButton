#pragma once
#include "Object3D.h"
#include <PlayerOption.h>
#include <IBossAttack.h>
#include "Timer.h"
#include <HitEffect.h>
#include "Hpbar.h"
class Boss :
    public Object3D
{
public:
    Boss(){};

    void Init();

    void Update();
    void Draw();

    void Hit(PlayerOption* other);

    const float maxHealth = 350;
    float health = maxHealth;

    enum class State {
        Center,
        Down,
        SumStates
    } state = State::Center;

    enum class AttackType {
        Idle,
        Bullets,
        Bar1,
        Bar2,
        AoE,
        SumTypes
    } attackType = AttackType::Idle;

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

    //状態遷移ごとの初期化処理
    void ChangeState(State next);
    void ChangeAttack(AttackType next);
    void ChangePhase(int next);

    void UpdateCol();

    void MoveTo(Vec3 goal, float speed);

    CircleCollider col;

    list<unique_ptr<IBossAttack>> bossAttacks;

    Timer attackTimer[(int)AttackType::SumTypes];
    Timer phaseTimer[4];
    Timer stateTimer[(int)State::SumStates];

    Timer bulletTimer;

    int phase = 0;

    //ボスが真ん中にいる秒数
    const int MaxBackCoolTime = 120;
    int backCoolTime = MaxBackCoolTime;
    

private:
    static unique_ptr<Boss> current;
    //HPバー
    Hpbar hpBar_;
    //ヒット時エフェクト
    std::list< std::unique_ptr<HitEffect>> hitEffect;

public:
    static Boss* Create();
    static Boss* GetCurrent();
};

