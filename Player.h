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

    //���݂̃v���C���[�̃C���X�^���X���擾
    static Player* GetCurrent();

    //�v���C���[������������Current�ɐݒ�
    static Player* Create();
private:

    static unique_ptr<Player> current;

    //�e�֘A
private:
    vector<PlayerBullet> bullets;

    void UpdateAllBullets();
    void DrawAllBullets();
};

