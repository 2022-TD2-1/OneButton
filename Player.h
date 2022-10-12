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

    //���݂̃v���C���[�̃C���X�^���X���擾
    static Player* GetCurrent();

    //�v���C���[������������Current�ɐݒ�
    static Player* Create();
private:
    PlayerOption opti = PlayerOption();

    static unique_ptr<Player> current;

    //�e�֘A
private:
    vector<PlayerBullet> bullets;

    void UpdateAllBullets();
    void DrawAllBullets();
};

