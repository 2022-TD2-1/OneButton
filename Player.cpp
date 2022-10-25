#include "Player.h"
#include <random>
#include "Input.h"
#include "Boss.h"

void Player::Init()
{
	this->scale = { .5f, .5f, .5f };


	for (int i = 0; i < 3; i++) {
		hps_.emplace_back();
		hps_.back().Ini(0 - 17 + (3 * i));
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
	//����ł���Ƃ�
	if (health <= 0) {
		DeadEffect();
		UpdateMatrix();
	}
	//�����Ă���Ƃ�
	else if (health > 0) {
		if (isCanAttack == true) {
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

		//�ړ����ʂ����]��̈ʒu���v�Z
		Matrix moveTemp = Matrix::Identity();
		moveTemp *= Matrix::Translation({ PlayerParams::circleR, 0.f, 0.f });
		moveTemp *= Matrix::RotZ(DegToRad(x * PlayerParams::degPerMove));

		this->rotation.z = DegToRad(x * PlayerParams::degPerMove + 90);

		//��]��̈ʒu�Ɉړ����Ď��g�̍s����X�V
		this->position = { moveTemp[3][0], moveTemp[3][1], moveTemp[3][2] };
		UpdateMatrix();
		UpdateCollisionPos();

		if (coolTime > 0) {
			coolTime--;
		}


		//�_���[�W���󂯂��Ƃ��ɓ_�ł���
		if (coolTime % 6 == 0)color_ = { 0.5f, 1.0f, 1.0f, 1.0f };
		else color_ = { 0.5f, 1.0f, 1.0f, 0.0f };

		if (Boss::GetCurrent()->isActive) {
			if (this->state == State::Move)
			{
				bulletTimer.Update();
			}
			if (this->state == State::Stop)
			{
				bulletTimer.Start();
			}
		}

		prePos = position;
	}
	UpdateAllBullets();
#pragma region TraceEffect(�v���C���[�̈ړ���)
	Vec3 newPos = (Vec3(0, 0, 0) - position).Norm() * 0.4f;
	Vec3 moveVec = -(Vec3(0, 0, 0) - position).Norm();
	newPos.x = position.x - newPos.x;
	newPos.y = position.y - newPos.y;
	newPos.z = position.z - newPos.z;
	std::unique_ptr<TraceEffect> newEffect = std::make_unique<TraceEffect>();
	newEffect->Ini(newPos, moveVec);
	trsEffect_.emplace_back(std::move(newEffect));
	//�G�t�F�N�g�X�V
	for (std::unique_ptr<TraceEffect>& effect : trsEffect_) {
		effect->Update();
	}
	//�G�t�F�N�g���f���[�g����
	trsEffect_.remove_if([](std::unique_ptr<TraceEffect>& effect)
		{
			return effect->GetDead();
		});
#pragma endregion

	//HP�I�u�W�F�N�g�X�V
	for (auto& itr : hps_)
	{
		if (itr.GetActive() == true) {
			itr.Update();
		}
	}
	//�G�t�F�N�g���f���[�g����
	hps_.remove_if([](PlayerHP& effect)
		{
			return effect.GetDead();
		});
	//���񂾍ۂ̃G�t�F�N�g�X�V
	for (std::unique_ptr<HitEffect>& effect : deadEffect) {
		effect->Update();
	}
	//���񂾍ۂ̃G�t�F�N�g���f���[�g����
	deadEffect.remove_if([](std::unique_ptr<HitEffect>& effect)
		{
			return effect->GetAllDead();
		});
}

void Player::Draw()
{
	if (isPlayerDisplay == true) {
		DrawAllBullets();
		(*this->brightnessCB.contents) = color_;
		Object3D::Draw();
		for (auto itr = opti.begin(); itr != opti.end(); itr++)
		{
			itr->Draw();
		}
		//HP�I�u�W�F�N�g�`��
		for (auto& itr : hps_)
		{
			itr.Draw();
		}

		//�G�t�F�N�g�X�V
		for (std::unique_ptr<TraceEffect>& effect : trsEffect_) {
			effect->Draw();
		}
	}

	//�G�t�F�N�g�`��
	for (std::unique_ptr<HitEffect>& effect : deadEffect) {
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

void Player::DeadEffect()
{
	if (deadEffectTime < maxDeadEffectTime) {
		deadEffectTime++;
	}
	//�v���C���[���k����
	if (deadEffectTime <= 60) {
		//�����V�[�h������
		std::random_device seed_gen;
		//�����Z���k�E�c�C�X�^�[�̗����G���W��
		std::mt19937_64 engine(seed_gen());
		//�ړ����x
		std::uniform_real_distribution<float> transDistX(-0.2f, 0.2f);
		std::uniform_real_distribution<float> transDistY(-0.2f, 0.2f);
		//�v���C���[���k����
		Vec3 dist = { transDistX(engine),transDistY(engine) ,0 };

		position = prePos + dist;
	}
	//�������Ď��͂ɃG�t�F�N�g���U��΂�
	else if (deadEffectTime <= 120) {
		//�v���C���[������
		isPlayerDisplay = false;
		if (deadEffectTime % 8 == 0) {
			std::unique_ptr<HitEffect> newEffect = std::make_unique<HitEffect>();
			newEffect->Ini(position, 3);
			deadEffect.emplace_back(std::move(newEffect));
		}
	}

	if (deadEffectTime >= 120) {
		if (deadEffect.size() <= 0) {
			isDead = true;
		}
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