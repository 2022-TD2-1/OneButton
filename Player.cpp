#include "Player.h"

#include "Input.h"
#include "Boss.h"

void Player::Init()
{
	this->scale = { .5f, .5f, .5f };
	

	for (int i = 0; i < 3; i++) {
		hps_.emplace_back();
		hps_.back().Ini(0 - 20 + (3 * i));
	}

	bulletTimer.Start();
	bulletTimer.SetOnTimeFunction(
		[&, this](void)
		{
			RegisterBullet(((Vec3)Boss::GetCurrent()->position - position).SetLength(bulletSpeed));
		}
	);
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
	//キーが押されたら分身を自分の座標に追加
	if (Input::Key::Triggered(DIK_SPACE))
	{
		opti.emplace_back();
		opti.back().x = this->x;
	}
	//キーが離されたら自分を分身の座標に移動
	if (Input::Key::Released(DIK_SPACE))
	{
		if (opti.size() > 0) {
			this->x = opti.back().x;
		}
	}

	//移動総量から回転後の位置を計算
	Matrix moveTemp = Matrix::Identity();
	moveTemp *= Matrix::Translation({ PlayerParams::circleR, 0.f, 0.f });
	moveTemp *= Matrix::RotZ(DegToRad(x * PlayerParams::degPerMove));

	this->rotation.z = DegToRad(x * PlayerParams::degPerMove + 90);

	//回転後の位置に移動して自身の行列を更新
	this->position = { moveTemp[3][0], moveTemp[3][1], moveTemp[3][2] };
	UpdateMatrix();
	UpdateCollisionPos();

	if (Input::Key::Released(DIK_SPACE))
	{
		if (opti.size() > 0) {
			opti.back().ChangeState(PlayerOption::State::Attack);
		}
	}
	else if (Input::Key::Triggered(DIK_SPACE))
	{
		opti.back().ChangeState(PlayerOption::State::Move);
	}
	for (auto itr = opti.begin(); itr != opti.end();)
	{
		itr->Update();

		if (itr->state == PlayerOption::State::Back)
		{
			itr = opti.erase(itr);
		}
		else
		{
			itr++;
		}
	}

	if (coolTime > 0) {
		coolTime--;
	}
	//HPオブジェクト更新
	for (auto& itr : hps_)
	{
		if (itr.GetActive() == true) {
			itr.Update();
		}
	}
	//エフェクトをデリートする
	hps_.remove_if([](PlayerHP& effect)
		{
			return effect.GetDead();
		});

	//ダメージを受けたときに点滅する
	if (coolTime % 6 == 0)color_ = { 0.5f, 1.0f, 1.0f, 1.0f };
	else color_ = { 0.5f, 1.0f, 1.0f, 0.0f };

	if (this->state == State::Move)
	{
		bulletTimer.Update();
	}
	if (this->state == State::Stop)
	{
		bulletTimer.Start();
	}

	//スペースを押していない間生成する(プレイヤーの移動跡)
	//if (!Input::Key::Down(DIK_SPACE)) {
		Vec3 newPos = (Vec3( 0, 0, 0 ) - position).Norm() * 0.4f;
		Vec3 moveVec = -(Vec3(0, 0, 0) - position).Norm();
		newPos.x = position.x - newPos.x;
		newPos.y = position.y - newPos.y;
		newPos.z = position.z - newPos.z;
		std::unique_ptr<TraceEffect> newEffect = std::make_unique<TraceEffect>();
		newEffect->Ini(newPos, moveVec);
		trsEffect_.emplace_back(std::move(newEffect));
	//}
	//エフェクト更新
	for (std::unique_ptr<TraceEffect>& effect : trsEffect_) {
		effect->Update();
	}
	//エフェクトをデリートする
	trsEffect_.remove_if([](std::unique_ptr<TraceEffect>& effect)
		{
			return effect->GetDead();
		});

	UpdateAllBullets();
}

void Player::Draw()
{
	DrawAllBullets();

	(*this->brightnessCB.contents) = color_;
	Object3D::Draw();
	for (auto itr = opti.begin(); itr != opti.end(); itr++)
	{
		itr->Draw();
	}
	//HPオブジェクト描画
	for (auto& itr : hps_)
	{
		itr.Draw();
	}

	//エフェクト更新
	for (std::unique_ptr<TraceEffect>& effect : trsEffect_) {
		effect->Draw();
	}
}

void Player::Damage(int damage)
{
	if (coolTime <= 0) {
		health -= damage;
		coolTime = maxCoolTime;
		hps_.back().SetActive();
	}
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

void Player::UpdateCollisionPos()
{
	col.x = position.x;
	col.y = position.y;
	col.r = scale.x;
}

void Player::UpdateAllBullets()
{
	for (auto itr = bullets.begin(); itr != bullets.end();)
	{
		itr->Update();

		if (itr->del)
		{
			itr = bullets.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void Player::DrawAllBullets()
{
	for (auto b : bullets) b.Draw();
}

void Player::RegisterBullet(Vec3 vel)
{
	bullets.emplace_back(vel);
}

unique_ptr<Player> Player::current = nullptr;