#include "Player.h"
#include "Input.h"

void Player::Init()
{
	opti.model = ModelManager::Get("Cube");
	opti.Ini();
}

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
			x--;
		}
		else
		{
			x++;
		}
	}
	//キーが押されたら分身を自分の座標に移動
	if (Input::Key::Triggered(DIK_SPACE))
	{
		opti.x = this->x;
	}
	//キーが離されたら自分を分身の座標に移動
	if (Input::Key::Released(DIK_SPACE))
	{
		this->x = opti.x;
	}

	//移動総量から回転後の位置を計算
	Matrix moveTemp = Matrix::Identity();
	moveTemp *= Matrix::Translation({ PlayerParams::circleR, 0.f, 0.f });
	moveTemp *= Matrix::RotZ(DegToRad(x * PlayerParams::degPerMove));

	//回転後の位置に移動して自身の行列を更新
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