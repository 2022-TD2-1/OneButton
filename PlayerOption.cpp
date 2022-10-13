#include "PlayerOption.h"
#include "Input.h"
#include "Parameters.h"

void PlayerOption::Update()
{
	//TODO: �^���v���O����������
	if (Input::Key::Released(DIK_SPACE))
	{
		ChangeState(State::Attack);
	}
	else if(Input::Key::Triggered(DIK_SPACE))
	{
		ChangeState(State::Move);
	}

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
	
	//�ړ����ʂ����]��̈ʒu���v�Z
	Matrix moveTemp = Matrix::Identity();
	moveTemp *= Matrix::Translation({ PlayerParams::circleR, 0.f, 0.f });
	moveTemp *= Matrix::RotZ(DegToRad(x * PlayerParams::degPerMove));

	//��]��̈ʒu�Ɉړ����Ď��g�̍s����X�V
	this->position = { moveTemp[3][0], moveTemp[3][1], moveTemp[3][2] };
	UpdateMatrix();
}

void PlayerOption::Draw()
{
	(*this->brightnessCB.contents) = Float4{0.5f, 1.0f, 1.0f, 1.0f};
	if(state != State::Invis)Object3D::Draw("white");
}

void PlayerOption::MoveUpdate()
{
	x+= 1.5f;
}

void PlayerOption::AttackUpdate()
{
	//TODO: �U�������ɕύX
	if (stateTimer[(int)State::Attack] > PlayerParams::attackTime)
	{
		ChangeState(State::Back);
	}
}

void PlayerOption::BackUpdate()
{
	//TODO: �v���C���[�Ɍ����������ɕύX
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
		break;
	case PlayerOption::State::Attack:
		break;
	case PlayerOption::State::Back:
		break;
	case PlayerOption::State::Invis:

		break;
	default:
		break;
	}
}
