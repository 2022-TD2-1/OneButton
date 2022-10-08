#include "Player.h"
#include "Input.h"

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
			x++;
		}
		else
		{
			x--;
		}
	}
	//�L�[�������ꂽ��i�s�����𔽓]
	if (Input::Key::Triggered(DIK_SPACE))
	{
		facing = facing == Side::CounterClock ?
			Side::Clock :
			Side::CounterClock;
	}

	//�ړ����ʂ����]��̈ʒu���v�Z
	Matrix moveTemp = Matrix::Identity();
	moveTemp *= Matrix::Translation({ PlayerParams::circleR, 0.f, 0.f });
	moveTemp *= Matrix::RotZ(DegToRad(x * PlayerParams::degPerMove));

	//��]��̈ʒu�Ɉړ����Ď��g�̍s����X�V
	this->position = { moveTemp[3][0], moveTemp[3][1], moveTemp[3][2] };
	UpdateMatrix();
}

void Player::Draw()
{
	Object3D::Draw();
}

Player* Player::GetCurrent()
{
	return &current;
}

Player* Player::Create()
{
	current = Player();
	return &current;
}

void Player::UpdateAllBullets()
{
	for (auto itr = bullets.begin(); itr != bullets.end();)
	{
		itr->Update();
		if (itr->del) itr = bullets.erase(itr);
		else itr++;
	}
}

void Player::DrawAllBullets()
{
	for (auto& bullet : bullets)
	{
		bullet.Draw();
	}
}

Player Player::current;