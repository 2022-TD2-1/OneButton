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
	//�L�[�������ꂽ�番�g�������̍��W�ɒǉ�
	if (Input::Key::Triggered(DIK_SPACE))
	{
		opti.emplace_back();
		opti.back().x = this->x;
	}
	//�L�[�������ꂽ�玩���𕪐g�̍��W�Ɉړ�
	if (Input::Key::Released(DIK_SPACE))
	{
		if (opti.size() > 0) {
			this->x = opti.back().x;
		}
	}

	//�ړ����ʂ����]��̈ʒu���v�Z
	Matrix moveTemp = Matrix::Identity();
	moveTemp *= Matrix::Translation({ PlayerParams::circleR, 0.f, 0.f });
	moveTemp *= Matrix::RotZ(DegToRad(x * PlayerParams::degPerMove));

	this->rotation.z = DegToRad(x * PlayerParams::degPerMove + 90);

	//��]��̈ʒu�Ɉړ����Ď��g�̍s����X�V
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
	//�_���[�W���󂯂��Ƃ��ɓ_�ł���
	if (coolTime % 6 == 0)color_ = { 0.5f, 1.0f, 1.0f, 1.0f };
	else color_ = { 0.5f, 1.0f, 1.0f, 0.0f };

	//�X�y�[�X�������Ă��Ȃ��Ԑ�������
	if (!Input::Key::Down(DIK_SPACE)) {
		std::unique_ptr<TraceEffect> newEffect = std::make_unique<TraceEffect>();
		newEffect->Ini(position);
		trsEffect_.emplace_back(std::move(newEffect));
	}
	//�G�t�F�N�g�X�V
	for (std::unique_ptr<TraceEffect>& effect : trsEffect_) {
		effect->Update();
	}
	//�G�t�F�N�g���f���[�g����
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

	//�G�t�F�N�g�X�V
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