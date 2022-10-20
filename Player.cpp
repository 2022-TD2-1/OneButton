#include "Player.h"

#include "Input.h"

void Player::Init()
{
	this->scale = { .5f, .5f, .5f };
	for (int i = 0; i < maxhealth; i++) {
		hpObj[i].model = ModelManager::Get("Sphere");
		hpObj[i].position.x = 0 - 5 + (5 * i);
		hpObj[i].position.y = -10;
		hpObj[i].position.z = 0;
		hpObj[i].rotation = { 0,0,0 };
		hpObj[i].scale = { 1,1,1 };
		hpObj[i].UpdateMatrix();
	}
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

	if (coolTime > 0)coolTime--;
	//ダメージを受けたときに点滅する
	if (coolTime % 6 == 0)color_ = { 0.5f, 1.0f, 1.0f, 1.0f };
	else color_ = { 0.5f, 1.0f, 1.0f, 0.0f };

	//スペースを押していない間生成する
	if (!Input::Key::Down(DIK_SPACE)) {
		std::unique_ptr<TraceEffect> newEffect = std::make_unique<TraceEffect>();
		newEffect->Ini(position);
		trsEffect_.emplace_back(std::move(newEffect));
	}
	//エフェクト更新
	for (std::unique_ptr<TraceEffect>& effect : trsEffect_) {
		effect->Update();
	}
	//エフェクトをデリートする
	trsEffect_.remove_if([](std::unique_ptr<TraceEffect>& effect)
		{
			return effect->GetDead();
		});
}

void Player::Draw()
{
	(*this->brightnessCB.contents) = color_;
	Object3D::Draw();
	for (auto itr = opti.begin(); itr != opti.end(); itr++)
	{
		itr->Draw();
	}
	for (int i = 0; i < maxhealth; i++) {
		hpObj[i].Draw("white");
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

unique_ptr<Player> Player::current = nullptr;