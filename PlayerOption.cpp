#include "PlayerOption.h"
#include "Input.h"
#include "Parameters.h"

void PlayerOption::Update()
{
	//TODO: 疑似プログラムを書く
	if (Input::Key::Released(DIK_SPACE))
	{
		state = State::Attack;
	}
	else if(Input::Key::Triggered(DIK_SPACE))
	{
		state = State::Move;
	}

	void (PlayerOption:: * PUpdtArray[]) () =
	{
		&PlayerOption::MoveUpdate,
		&PlayerOption::AttackUpdate,
		&PlayerOption::BackUpdate
	};

	(this->*PUpdtArray[(int)state])();

	//ステートごとのアップデートを呼ぶ
	//Moveならxをspeed分増加
	
	//移動総量から回転後の位置を計算
	Matrix moveTemp = Matrix::Identity();
	moveTemp *= Matrix::Translation({ PlayerParams::circleR, 0.f, 0.f });
	moveTemp *= Matrix::RotZ(DegToRad(x * PlayerParams::degPerMove));

	//回転後の位置に移動して自身の行列を更新
	this->position = { moveTemp[3][0], moveTemp[3][1], moveTemp[3][2] };
	UpdateMatrix();
}

void PlayerOption::Draw()
{
	(*this->brightnessCB.contents) = Float4{0.5f, 1.0f, 1.0f, 1.0f};
	Object3D::Draw("white");
}

void PlayerOption::MoveUpdate()
{
	x+= 1.5f;
}

void PlayerOption::AttackUpdate()
{
	//TODO: 攻撃処理に変更
	this->state = State::Back;
}

void PlayerOption::BackUpdate()
{
}
