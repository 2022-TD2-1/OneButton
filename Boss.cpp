#include "Boss.h"
#include <Parameters.h>
#include "ModelManager.h"
#include <ApUtil.h>
#include "BossBullet.h"
#include "BossLaser.h"
#include <SceneManager.h>
#include <ResultScene.h>
#include <random>
#include <BossAoE.h>
#include "BossCrossLaser.h"
unique_ptr<Boss> Boss::current = nullptr;

void Boss::Init(Camera* camera)
{
	timer_ = GameTimer::GetInstance();
	Object3D::Object3D();
	this->model = ModelManager::Get("Boss");

	for (auto& tm : phaseTimer) tm.Start();
	for (auto& tm : attackTimer) tm.Start();
	for (auto& tm : stateTimer) tm.Start();
	bulletTimer.Start();

	hpBar_.Ini(maxHealth, Vec3(0, 10, 0));
	position.z = -20;

	camera_ = camera;

	countDown_.Ini();

	bossKnockSE = "bossKnock";

	scale = { 1.5f, 1.5f, 1.5f };

	rotation.x = -(PI / 16);

	shockWaveObj.model = ModelManager::Get("Sphere");
	*shockWaveObj.brightnessCB.contents = { 1.f, 0.5f, 0.5f, .4f };
	shockWaveObj.position = { 0,0,0 };
	shockWaveObj.scale = { 0,0,0 };
	shockWaveObj.UpdateMatrix();
}

void Boss::Update()
{
	//����ł���Ƃ�
	if (health <= 0) {

		DeadEffect();
		UpdateMatrix();
		timer_->StopTimer();
	}
	else {
		//�o�ꉉ�o�̎�
		if (isActive == false) {
			if (position.z < 0) {
				player_->SetCanNotAttack();
				position.z += 0.1f;
			}
			else {
				position.z = 0;
				if (countDown_.GetEnd() == false) {
					//�J�E���g�_�E����\��
					countDown_.SetDisplay();
				}
				else if (countDown_.GetEnd() == true) {
					//�J�E���g�_�E�����I�������Q�[���X�^�[�g
					isActive = true;
					timer_->StartTimer();
					player_->SetCanAttack();
				}
				countDown_.Update();

			}

			if (position.z >= -0.3f && position.z <= -0.1f) {
				//�J�����V�F�C�N
				camera_->ShakeSet(40, 0.7, 3);
			}
		}
		//�Q�[�����n�܂�����
		else if (isActive == true) {

			if (testTime >= 0) {
				testTime--;
				position = { 0,0,0 };
			}

			void (Boss:: * BUpdtArray[]) () =
			{
				&Boss::CenterUpdate,
				&Boss::DownUpdate
			};

			(this->*BUpdtArray[(int)state])();

			void (Boss:: * BUpdtArray2[]) () =
			{
				&Boss::P1Update,
				&Boss::P2Update,
				&Boss::P3Update
			};

			(this->*BUpdtArray2[(int)phase])();

			if (state != State::Down)
			{

				void (Boss:: * BUpdtArray3[]) () =
				{
					&Boss::IdleUpdate,
					&Boss::BulletsUpdate,
					&Boss::Bar1Update,
					&Boss::Bar2Update,
					&Boss::AoEUpdate
				};

				(this->*BUpdtArray3[(int)attackType])();
			}

			UpdateAllAttacks();

		}
	}
	//�G�t�F�N�g�X�V
	for (std::unique_ptr<HitEffect>& effect : hitEffect) {
		effect->Update();
	}
	//�G�t�F�N�g���f���[�g����
	hitEffect.remove_if([](std::unique_ptr<HitEffect>& effect)
		{
			return effect->GetAllDead();
		});

	hpBar_.Update(health);

	this->col.x = this->position.x;
	this->col.y = this->position.y;
	this->col.r = this->scale.x;

	UpdateMatrix();

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

void Boss::Draw()
{
	if (isBossDisplay == true) {
		Object3D::Draw();
	}
	if (health > 0) {
		DrawAllAttacks();
	}

	countDown_.Draw();

	hpBar_.Draw();
	//�G�t�F�N�g�`��
	for (std::unique_ptr<HitEffect>& effect : hitEffect) {
		effect->Draw();
	}

	//�G�t�F�N�g�`��
	for (std::unique_ptr<HitEffect>& effect : deadEffect) {
		effect->Draw();
	}

	if (isActiveShocWave == true) {
		shockWaveObj.Draw("white");
	}
}

void Boss::Hit(PlayerOption* other)
{
	//this->health -= PlayerParams::damage;
	if (isActive == true && health > 0) {
		if (state == State::Center && !isReturning)
		{
			health -= 2.f * (other->power * (other->power / 2));
			//kb����
			float kbPower = 1.0f * other->power * other->power;
			Vec3 dir = (Vec3)this->position - other->position;
			dir.SetLength(min(kbPower, 8.0f));
			this->position = dir;

			float l = ((Vec3)this->position).GetSquaredLength();

			if (((Vec3)this->position).GetSquaredLength() >= 8.0f * 8.0f - 0.1f)
			{
				SoundManager::Play(bossKnockSE);
				this->state = State::Down;
				this->laneX = other->x - 180 / PlayerParams::degPerMove;
				isShocWave = true;	//�Ռ��g���o���t���O���I���ɂ���
			}
			UpdateMatrix();
			this->UpdateCol();

			std::unique_ptr<HitEffect> newEffect = std::make_unique<HitEffect>();
			newEffect->Ini(position, other->power);
			hitEffect.emplace_back(std::move(newEffect));
			//�J�����V�F�C�N
			camera_->ShakeSet(20 * other->power, 0.3, other->power);
		}
		else if (!isReturning)
		{
			SoundManager::Play("bossKnock");
			health -= 1.f * other->power;
			//kb����
			laneX -= 2.0f * other->power;
			//�ړ����ʂ����]��̈ʒu���v�Z
			Matrix moveTemp = Matrix::Identity();
			moveTemp *= Matrix::Translation({ PlayerParams::circleR, 0.f, 0.f });
			moveTemp *= Matrix::RotZ(DegToRad(laneX * PlayerParams::degPerMove));

			//��]��̈ʒu�Ɉړ����Ď��g�̍s����X�V
			this->position = { moveTemp[3][0], moveTemp[3][1], moveTemp[3][2] };
			UpdateMatrix();
			//UpdateCollision();
		}
	}
}

void Boss::Hit()
{
	health -= 1.f;
}

void Boss::CenterUpdate()
{
	stateTimer[0].Update();
	MoveTo(Vec3(0, 0, 0), 0.1f);
	*this->brightnessCB.contents = { 1.0f, 1.0f, 1.0f, 1.0f };
	if (this->isReturning && (int)this->stateTimer[0].Check() % 500 < 250)
	{
		this->brightnessCB.contents->w = 0.25f;
	}
	if (isShocWave == true) {
		if (position.x == 0) {
			isActiveShocWave = true;	//�Ռ��g���o��
		}
	}
}

void Boss::DownUpdate()
{
	*this->brightnessCB.contents = { 1.0f, 0.0f, 0.0f, 1.0f };

	backCoolTime--;
	//�[���ɂȂ�����
	if (backCoolTime <= 0) {
		//�^�񒆂ɖ߂��Ă���
		state = State::Center;
		//�J�E���g���Z�b�g
		backCoolTime = MaxBackCoolTime;
		isReturning = true;
	}
}

void Boss::P1Update()
{
	phaseTimer[0].Update();
	if (attackType == AttackType::Idle)
	{
		//�X�e�b�v3�Ȃ�
		if (step >= 2)
		{
			if (attackTimer[(int)AttackType::Idle].Check() >= 2000.0)
			{
				phaseTimer->Subtract(phaseTimer[0].Check() - 1000.0);
				ChangeAttack(AttackType::AoE);//aoe
				step = 0;
			}
		}
		else if (step == 1)
		{
			if (attackTimer[(int)AttackType::Idle].Check() >= 2000.0)
			{//�X�e�b�v2�Ȃ�
				phaseTimer->Subtract(phaseTimer[0].Check() - 1000.0);
				ChangeAttack(AttackType::Bar2);//laser cross
				step++;
			}
		}
		else
		{
			if (attackTimer[(int)AttackType::Idle].Check() >= 4000.0)
			{//�X�e�b�v1�Ȃ�
				phaseTimer->Subtract(phaseTimer[0].Check() - 1000.0);
				ChangeAttack(AttackType::Bar1);//laser
				step++;
			}
		}
	}
	if (this->health < maxHealth * 3 / 4)
	{
		this->phase++;
	}
}

void Boss::P2Update()
{
	phaseTimer[1].Update();
	if (attackType == AttackType::Idle)
	{
		//�X�e�b�v4�Ȃ�
		if (step >= 3)
		{
			if (attackTimer[(int)AttackType::Idle].Check() >= 1000.0)
			{
				phaseTimer->Subtract(phaseTimer[0].Check() - 1000.0);
				ChangeAttack(AttackType::AoE);
				ChangeAttack(AttackType::AoE);
				step = 0;
			}
		}
		else if (step == 2)
		{
			if (attackTimer[(int)AttackType::Idle].Check() >= 1000.0)
			{//�X�e�b�v3�Ȃ�
				phaseTimer->Subtract(phaseTimer[0].Check() - 1000.0);
				if (ApUtil::Chance(50))
				{
					ChangeAttack(AttackType::Bar2);
				}
				else
				{
					ChangeAttack(AttackType::Bar1);
					ChangeAttack(AttackType::Bullets);
				}
				step++;
			}
		}
		else if (step == 1)
		{
			if (attackTimer[(int)AttackType::Idle].Check() >= 1000.0)
			{//�X�e�b�v2�Ȃ�
				phaseTimer->Subtract(phaseTimer[0].Check() - 1000.0);
				if (ApUtil::Chance(50))
				{
					ChangeAttack(AttackType::Bar1);
				}
				else
				{
					ChangeAttack(AttackType::Bullets);
				}
				step++;
			}
		}
		else
		{
			if (attackTimer[(int)AttackType::Idle].Check() >= 4000.0)
			{//�X�e�b�v1�Ȃ�
				phaseTimer->Subtract(phaseTimer[0].Check() - 1000.0);
				//ChangeAttack((AttackType)ApUtil::RNG(1, 3, true));
				if (ApUtil::Chance(50))
				{
					ChangeAttack(AttackType::Bar1);
				}
				else
				{
					ChangeAttack(AttackType::Bullets);
				}
				step++;
			}
		}
	}
	if (this->health < maxHealth / 4)
	{
		this->phase++;
	}
}

void Boss::P3Update()
{
	phaseTimer[2].Update();
	if (attackType == AttackType::Idle)
	{
		//�X�e�b�v5�Ȃ�
		if (step >= 4)
		{
			if (attackTimer[(int)AttackType::Idle].Check() >= 1000.0)
			{
				phaseTimer->Subtract(phaseTimer[0].Check() - 1000.0);
				ChangeAttack(AttackType::AoE);
				ChangeAttack(AttackType::AoE);
				ChangeAttack(AttackType::AoE);
				step = 0;
			}
		}
		else if (step == 3)
		{
			if (attackTimer[(int)AttackType::Idle].Check() >= 500.0)
			{//�X�e�b�v4�Ȃ�
				phaseTimer->Subtract(phaseTimer[0].Check() - 1000.0);
				ChangeAttack(AttackType::Bar2);
				step++;
			}
		}
		else if (step == 2)
		{
			if (attackTimer[(int)AttackType::Idle].Check() >= 1000.0)
			{//�X�e�b�v3�Ȃ�
				phaseTimer->Subtract(phaseTimer[0].Check() - 1000.0);
				ChangeAttack(AttackType::Bar2);
				ChangeAttack(AttackType::Bullets);
				step++;
			}
		}
		else if (step == 1)
		{
			if (attackTimer[(int)AttackType::Idle].Check() >= 500.0)
			{//�X�e�b�v2�Ȃ�
				phaseTimer->Subtract(phaseTimer[0].Check() - 1000.0);
				ChangeAttack(AttackType::Bar1);
				step++;
			}
		}
		else
		{
			if (attackTimer[(int)AttackType::Idle].Check() >= 4000.0)
			{//�X�e�b�v1�Ȃ�
				phaseTimer->Subtract(phaseTimer[0].Check() - 1000.0);
				ChangeAttack(AttackType::Bar1);
				ChangeAttack(AttackType::Bullets);
				step++;
			}
		}
	}
}

void Boss::IdleUpdate()
{
	attackTimer[(int)AttackType::Idle].Update();
}

void Boss::BulletsUpdate()
{
	Timer* timer = &attackTimer[(int)AttackType::Bullets];
	timer->Update();
	bulletTimer.Update();
	if (bulletTimer.Check() >= BossParams::bulletCD)
	{
		bulletTimer.Subtract(BossParams::bulletCD);
		double deg = (int)timer->Check() / 250;
		deg *= BossParams::bulletDeg;

		bossAttacks.emplace_back(new BossBullet(Vec3(ApUtil::ConvertDegDistToX(1, deg), ApUtil::ConvertDegDistToY(1, deg), 0).SetLength(BossParams::bulletSpeed)));
	}
	else {
		int a = 0;
	}

	//bullet��Ԃ̌p������
	if (timer->Check() > 3000.0)
	{
		ChangeAttack(AttackType::Idle);
	}
}

void Boss::Bar1Update()
{
	Timer* timer = &attackTimer[(int)AttackType::Bar1];
	timer->Update();

	if (timer->Check() > BossLaser::totalTime)
	{
		ChangeAttack(AttackType::Idle);
	}
}

void Boss::Bar2Update()
{
	Timer* timer = &attackTimer[(int)AttackType::Bar2];
	timer->Update();

	if (timer->Check() > BossLaser::totalTime)
	{
		ChangeAttack(AttackType::Idle);
	}
}

void Boss::AoEUpdate()
{
	Timer* timer = &attackTimer[(int)AttackType::AoE];
	timer->Update();

	if (timer->Check() > BossAoE::totalTime)
	{
		ChangeAttack(AttackType::Idle);
	}
}

void Boss::UpdateAllAttacks()
{
	for (auto itr = bossAttacks.begin(); itr != bossAttacks.end();)
	{
		(*itr)->Update();
		if ((*itr)->del)
		{
			itr = bossAttacks.erase(itr);
		}
		else
		{
			itr++;
		}
	}

	for (auto itr = bossAoEs.begin(); itr != bossAoEs.end();)
	{
		(*itr)->Update();
		if ((*itr)->del)
		{
			itr = bossAoEs.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void Boss::DrawAllAttacks()
{
	for (auto& attack : bossAttacks)
	{
		attack->Draw();
	}
	for (auto& attack : bossAoEs)
	{
		dynamic_cast<BossAoE*>(attack.get())->DrawEnt();
	}
}

void Boss::DrawAoEs()
{
	for (auto& attack : bossAoEs)
	{
		attack->Draw();
	}
}

void Boss::ChangeState(State next)
{
	state = next;
	stateTimer[(int)next].Start();

	switch (next)
	{
	case Boss::State::Center:
		break;
	case Boss::State::Down:
		break;
	case Boss::State::SumStates:
		break;
	default:
		break;
	}
}

void Boss::ChangeAttack(AttackType next)
{
	attackType = next;
	attackTimer[(int)next].Start();

	switch (next)
	{
	case Boss::AttackType::Idle:
		break;
	case Boss::AttackType::Bullets:
		bulletTimer.Start();
		break;
	case Boss::AttackType::Bar1:
		bossAttacks.emplace_back(new BossLaser((float)ApUtil::RNG(1, 360) * PI / 180));
		break;
	case Boss::AttackType::Bar2:
		bossAttacks.emplace_back(new BossCrossLaser((float)ApUtil::RNG(1, 360) * PI / 180));
		break;
	case Boss::AttackType::AoE:
		bossAoEs.emplace_back(new BossAoE((float)ApUtil::RNG(1, 360) * PI / 180));
		break;
	case Boss::AttackType::SumTypes:
		break;
	default:
		break;
	}
}

void Boss::ChangePhase(int next)
{
	phase = next;
	phaseTimer[next].Start();

	switch (next)
	{
	case 1:
		break;
	default:
		break;
	}
}

void Boss::UpdateCol()
{
	this->col.x = this->position.x;
	this->col.y = this->position.y;
	this->col.r = this->scale.x;
}

void Boss::MoveTo(Vec3 goal, float speed)
{
	Vec3 dir = goal - this->position;
	if (dir.GetSquaredLength() < speed * speed)
	{
		position = goal;
		isReturning = false;
		return;
	}
	this->position = (Vec3)this->position + dir.SetLength(speed);
}

void Boss::DeadEffect()
{
	if (deadEffectTime == 0) {
		SoundManager::Play("BossDead");
	}

	if (deadEffectTime < maxDeadEffectTime) {
		deadEffectTime++;
	}
	//�{�X���k����
	if (deadEffectTime <= 120) {
		if (deadEffectTime == 119) {
			
		}
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
	else if (deadEffectTime <= 240) {
		
		//�{�X������
		isBossDisplay = false;
		if (deadEffectTime % 8 == 0) {
			SoundManager::Play("Explosion");
			std::unique_ptr<HitEffect> newEffect = std::make_unique<HitEffect>();
			newEffect->Ini(position, 4, true);
			deadEffect.emplace_back(std::move(newEffect));
		}
	}

	if (deadEffectTime >= 240) {
		if (deadEffect.size() <= 0) {
			isDead = true;
		}
	}
}

void Boss::ShockwaveUpdate()
{
	if (isActiveShocWave == true) {
		shockWaveObj.scale.x += 0.5f;
		shockWaveObj.scale.y += 0.5f;
		shockWaveObj.scale.z += 0.5f;
		if (shockWaveObj.scale.x >= 20) {
			isShocWave = false;
			isActiveShocWave = false;
			shockWaveObj.scale = { 0,0,0 };
		}
		shockWaveObj.UpdateMatrix();

		CircleCollider swcol;
		swcol.x = shockWaveObj.position.x;
		swcol.y = shockWaveObj.position.y;
		swcol.r = shockWaveObj.scale.x;

		for (auto itr = Player::GetCurrent()->opti.begin(); itr != Player::GetCurrent()->opti.end();)
		{
			if (swcol.Collide(itr->col))
			{
				itr = Player::GetCurrent()->opti.erase(itr);
			}
			else
			{
				itr++;
			}
		}
	}
}

Boss* Boss::Create()
{
	current = unique_ptr<Boss>(new Boss);
	return current.get();
}

Boss* Boss::GetCurrent()
{
	return current.get();
}
