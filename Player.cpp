#include "Player.h"
#include "Input.h"

void Player::Init()
{
	opti.model = ModelManager::Get("Cube");
	opti.Ini();
}

void Player::Update()
{
	//�L�[��������Ă���Ԃ͒�~��ԂɁA�����łȂ��Ȃ�ړ�
	if (Input::Key::Down(DIK_SPACE))
	{
		state = State::Stop;
	}
	else
	{
		state = State::Move;
		if (facing == Side::Clock)
		{
			x--;
		}
		else
		{
			x++;
		}
	}
	//�L�[�������ꂽ�番�g�������̍��W�Ɉړ�
	if (Input::Key::Triggered(DIK_SPACE))
	{
		opti.x = this->x;
	}
	//�L�[�������ꂽ�玩���𕪐g�̍��W�Ɉړ�
	if (Input::Key::Released(DIK_SPACE))
	{
		this->x = opti.x;
	}

	//�ړ����ʂ����]��̈ʒu���v�Z
	Matrix moveTemp = Matrix::Identity();
	moveTemp *= Matrix::Translation({ PlayerParams::circleR, 0.f, 0.f });
	moveTemp *= Matrix::RotZ(DegToRad(x * PlayerParams::degPerMove));

	//��]��̈ʒu�Ɉړ����Ď��g�̍s����X�V
	this->position = { moveTemp[3][0], moveTemp[3][1], moveTemp[3][2] };
	UpdateMatrix();

	opti.Update();
}

void Player::Draw()
{
	Object3D::Draw("white");
	opti.Draw();
}

Player* Player::GetCurrent()
{
	return current.get();
}

Player* Player::Create()
{
	current = unique_ptr<Player>(new Player());
	return current.get();
}

unique_ptr<Player> Player::current = nullptr;