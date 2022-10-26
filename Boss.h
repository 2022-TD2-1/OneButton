#pragma once
#include "Object3D.h"
#include <PlayerOption.h>
#include <IBossAttack.h>
#include "Timer.h"
#include "Hpbar.h"
#include <HitEffect.h>
#include <Camera.h>
#include "CountDown.h"
#include "GameTimer.h"
#include "Player.h"
#include <SoundManager.h>
class Boss :
    public Object3D
{
public:
    Boss(){};

    void Init(Camera* camera);

    void Update();
    void Draw();

    //分身に当たった場合
    void Hit(PlayerOption* other);
    //通常弾に当たった場合
    void Hit();

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
    void DrawAoEs();

    //状態遷移ごとの初期化処理
    void ChangeState(State next);
    void ChangeAttack(AttackType next);
    void ChangePhase(int next);

    void UpdateCol();

    void MoveTo(Vec3 goal, float speed);

    CircleCollider col;

    list<unique_ptr<IBossAttack>> bossAttacks;
    list<unique_ptr<IBossAttack>> bossAoEs;

    Timer attackTimer[(int)AttackType::SumTypes];
    Timer phaseTimer[4];
    Timer stateTimer[(int)State::SumStates];

    Timer bulletTimer;

    //円周上での座標
    float laneX = 0;

    int phase = 0;

    //ボスが真ん中にいる秒数
    const int MaxBackCoolTime = 120;
    int backCoolTime = MaxBackCoolTime;
    
    int isActive = false;

    bool isDead = false;
private:
    static unique_ptr<Boss> current;
    //HPバー
    Hpbar hpBar_;
    //ヒット時エフェクト
    std::list< std::unique_ptr<HitEffect>> hitEffect;

    //パワーコード
    int testTime = 10;

    Camera* camera_ = nullptr;

   
    Vec3 prePos;	//ボスのいた場所を保存する
    const int maxDeadEffectTime = 600;
    int deadEffectTime = 0;
    bool isBossDisplay = true;		//ボスを表示するフラグ
    //ヒット時エフェクト
    std::list< std::unique_ptr<HitEffect>> deadEffect;
    void DeadEffect();	//死んだときの演出

    
    CountDown countDown_;
    GameTimer* timer_ = nullptr;

    int step = 0;
    Player* player_ = nullptr;

    SoundKey bossKnockSE;   //レーン上に載る攻撃を受けたとき

    Object3D shockWaveObj;
    bool isShocWave = false;
    bool isActiveShocWave = false;
    void ShockwaveUpdate();
public:
    static Boss* Create();
    static Boss* GetCurrent();

    void SetPlayer(Player* player) { player_ = player; }
};

