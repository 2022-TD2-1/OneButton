#include "Player.h"
#include "Input.h"

void Player::Update()
{
	//キーが押されている間は停止状態に、そうでないなら移動
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
	//キーが押されたら進行方向を反転
	if (Input::Key::Triggered(DIK_SPACE))
	{
		facing = facing == Side::CounterClock ?
			Side::Clock :
			Side::CounterClock;
	}

	//移動総量から回転後の位置を計算
	Matrix moveTemp = Matrix::Identity();
	moveTemp *= Matrix::Translation({ PlayerParams::circleR, 0.f, 0.f });
	moveTemp *= Matrix::RotZ(DegToRad(x * PlayerParams::degPerMove));

	//回転後の位置に移動して自身の行列を更新
	this->position = { moveTemp[3][0], moveTemp[3][1], moveTemp[3][2] };
	UpdateMatrix();
}

void Player::Draw()
{
	Object3D::Draw();
}
