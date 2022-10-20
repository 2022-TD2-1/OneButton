#include "PlayerOption.h"
#include "Input.h"
#include "Parameters.h"
#include <Boss.h>
#include <Player.h>

void PlayerOption::Ini() {
	position = { 100,100,0 };
}

void PlayerOption::Update()
{
	void (PlayerOption:: * PUpdtArray[]) () =
	{
		&PlayerOption::MoveUpdate,
		&PlayerOption::AttackUpdate,
		&PlayerOption::BackUpdate,
		&PlayerOption::InvisUpdate
	};

	(this->*PUpdtArray[(int)state])();

	stateTimer[(int)state]++;

	//�X�e�[�g���Ƃ̃A�b�v�f�[�g���Ă�
	//Move�Ȃ�x��speed������
	UpdateMatrix();
	this->col.x = position.x;
	this->col.y = position.y;
	this->col.r = scale.x;
}

void PlayerOption::Draw()
{
	(*this->brightnessCB.contents) = Float4{0.5f, 1.0f, 1.0f, 1.0f};
	if(state != State::Invis)Object3D::Draw("white");
}

void PlayerOption::MoveUpdate()
{
	power += 0.01f;
	x -= 1.5f * power;
	if (col.Collide(Boss::GetCurrent()->col))
	{
		Boss::GetCurrent()->Hit(this);
	}

	//�ړ����ʂ����]��̈ʒu���v�Z
	Matrix moveTemp = Matrix::Identity();
	moveTemp *= Matrix::Translation({ PlayerParams::circleR, 0.f, 0.f });
	moveTemp *= Matrix::RotZ(DegToRad(x * PlayerParams::degPerMove));
	//��]��̈ʒu�Ɉړ����Ď��g�̍s����X�V
	this->position = { moveTemp[3][0], moveTemp[3][1], moveTemp[3][2] };
	this->scale = Vec3((power - 1.0f) * 0.25f + .5f, (power - 1.0f) * 0.25f + .5f, (power - 1.0f) * 0.25f + .5f);
}

void PlayerOption::AttackUpdate()
{
	//TODO: �U�������ɕύX
	this->position = Vec3::Lerp(attackStartedPos, Vec3(0,0,0), (float)stateTimer[(int)State::Attack] / PlayerParams::attackTime);
	if (stateTimer[(int)State::Attack] > PlayerParams::attackTime)
	{
		ChangeState(State::Back);
	}

	if (col.Collide(Boss::GetCurrent()->col))
	{
		Boss::GetCurrent()->Hit(this);
		ChangeState(State::Back);
	}
}

void PlayerOption::BackUpdate()
{
	//TODO: �v���C���[�Ɍ����������ɕύX
	this->position = Vec3::Lerp(this->position, Player::GetCurrent()->position, (float)stateTimer[(int)State::Back] / PlayerParams::backTime);
	if (stateTimer[(int)State::Back] > PlayerParams::backTime)
	{
		ChangeState(State::Invis);
	}
}

void PlayerOption::InvisUpdate()
{
}

void PlayerOption::ChangeState(State next)
{
	state = next;
	stateTimer[(int)next] = 0;

	switch (next)
	{
	case PlayerOption::State::Move:
		power = 1.f;
		break;
	case PlayerOption::State::Attack:
		attackStartedPos = this->position;
		break;
	case PlayerOption::State::Back:
		break;
	case PlayerOption::State::Invis:

		break;
	default:
		break;
	}
}
