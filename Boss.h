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

    //���g�ɓ��������ꍇ
    void Hit(PlayerOption* other);
    //�ʏ�e�ɓ��������ꍇ
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

    //�_�E���A��_�E���̏���
    void CenterUpdate();
    void DownUpdate();

    //�t�F�[�Y���Ƃ̍U���p�^�[������
    void P1Update();
    void P2Update();
    void P3Update();

    //�U�����Ƃ̏���
    void IdleUpdate();
    void BulletsUpdate();
    void Bar1Update();
    void Bar2Update();
    void AoEUpdate();

    //�U���̃A�b�v�f�[�g�ƃh���[
    void UpdateAllAttacks();
    void DrawAllAttacks();
    void DrawAoEs();

    //��ԑJ�ڂ��Ƃ̏���������
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

    //�~����ł̍��W
    float laneX = 0;

    int phase = 0;

    //�{�X���^�񒆂ɂ���b��
    const int MaxBackCoolTime = 120;
    int backCoolTime = MaxBackCoolTime;
    
    int isActive = false;

    bool isDead = false;
private:
    static unique_ptr<Boss> current;
    //HP�o�[
    Hpbar hpBar_;
    //�q�b�g���G�t�F�N�g
    std::list< std::unique_ptr<HitEffect>> hitEffect;

    //�p���[�R�[�h
    int testTime = 10;

    Camera* camera_ = nullptr;

   
    Vec3 prePos;	//�{�X�̂����ꏊ��ۑ�����
    const int maxDeadEffectTime = 600;
    int deadEffectTime = 0;
    bool isBossDisplay = true;		//�{�X��\������t���O
    //�q�b�g���G�t�F�N�g
    std::list< std::unique_ptr<HitEffect>> deadEffect;
    void DeadEffect();	//���񂾂Ƃ��̉��o

    
    CountDown countDown_;
    GameTimer* timer_ = nullptr;

    int step = 0;
    Player* player_ = nullptr;

    SoundKey bossKnockSE;   //���[����ɍڂ�U�����󂯂��Ƃ�

    Object3D shockWaveObj;
    bool isShocWave = false;
    bool isActiveShocWave = false;
    void ShockwaveUpdate();
public:
    static Boss* Create();
    static Boss* GetCurrent();

    void SetPlayer(Player* player) { player_ = player; }
};

