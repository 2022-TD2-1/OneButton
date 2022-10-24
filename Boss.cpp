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
unique_ptr<Boss> Boss::current = nullptr;

void Boss::Init(Camera* camera)
{
	Object3D::Object3D();
	this->model = ModelManager::Get("Boss");

	for (auto& tm : phaseTimer) tm.Start();
	for (auto& tm : attackTimer) tm.Start();
	for (auto& tm : stateTimer) tm.Start();
	bulletTimer.Start();

	hpBar_.Ini(maxHealth, Vec3(0, 10, 0));
	position.z = -20;

	camera_ = camera;
}

void Boss::Update()
{
	//死んでいるとき
	if (health <= 0) {
		DeadEffect();
		UpdateMatrix();
	}
	else {
		//登場演出の時
		if (isActive == false) {
			if (position.z < 0) {
				position.z += 0.1;
			}
			else {
				position.z = 0;
				isActive = true;
				//カメラシェイク
				camera_->ShakeSet(40, 0.7, 3);
			}

		}
		//ゲームが始まった時
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
					&Boss::Bar1Update,/*
					&Boss::Bar2Update,*/
					&Boss::AoEUpdate
				};

				(this->*BUpdtArray3[(int)attackType])();
			}

			UpdateAllAttacks();

		}
	}
	//エフェクト更新
	for (std::unique_ptr<HitEffect>& effect : hitEffect) {
		effect->Update();
	}
	//エフェクトをデリートする
	hitEffect.remove_if([](std::unique_ptr<HitEffect>& effect)
		{
			return effect->GetAllDead();
		});

	hpBar_.Update(health);

	this->col.x = this->position.x;
	this->col.y = this->position.y;
	this->col.r = this->scale.x;

	UpdateMatrix();

	//死んだ際のエフェクト更新
	for (std::unique_ptr<HitEffect>& effect : deadEffect) {
		effect->Update();
	}
	//死んだ際のエフェクトをデリートする
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

	hpBar_.Draw();
	//エフェクト描画
	for (std::unique_ptr<HitEffect>& effect : hitEffect) {
		effect->Draw();
	}

	//エフェクト描画
	for (std::unique_ptr<HitEffect>& effect : deadEffect) {
		effect->Draw();
	}
}

void Boss::Hit(PlayerOption* other)
{
	//this->health -= PlayerParams::damage;
	if (isActive == true && health > 0) {
		if (other->state == PlayerOption::State::Attack)
		{
			health -= 2.f * (other->power * 3);
			//kb処理
			float kbPower = 1.0f * other->power * other->power;
			Vec3 dir = (Vec3)this->position - other->position;
			dir.SetLength(min(kbPower, 8.0f));
			this->position = dir;

			float l = ((Vec3)this->position).GetSquaredLength();

			if (((Vec3)this->position).GetSquaredLength() >= 8.0f * 8.0f - 0.1f)
			{
				this->state = State::Down;
			}
			UpdateMatrix();
			this->UpdateCol();

			std::unique_ptr<HitEffect> newEffect = std::make_unique<HitEffect>();
			newEffect->Ini(position, other->power);
			hitEffect.emplace_back(std::move(newEffect));
			//カメラシェイク
			camera_->ShakeSet(20 * other->power, 0.3, other->power);
		}
		else if (other->state == PlayerOption::State::Move)
		{
			health -= 1.f * other->power;
			//kb処理
		}
	}
}

void Boss::Hit()
{
	health -= 1.f;
}

void Boss::CenterUpdate()
{
	MoveTo(Vec3(0, 0, 0), 0.1f);
	*this->brightnessCB.contents = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void Boss::DownUpdate()
{
	*this->brightnessCB.contents = { 1.0f, 0.0f, 0.0f, 1.0f };
	backCoolTime--;
	//ゼロになったら
	if (backCoolTime <= 0) {
		//真ん中に戻っていく
		state = State::Center;
		//カウントリセット
		backCoolTime = MaxBackCoolTime;
	}
}

void Boss::P1Update()
{
	phaseTimer[0].Update();
	if (attackType == AttackType::Idle)
	{
		if (attackTimer[(int)AttackType::Idle].Check() >= 1000.0)
		{
			phaseTimer->Subtract(phaseTimer[0].Check() - 1000.0);
			ChangeAttack((AttackType)ApUtil::RNG(1, 3, true));
		}
	}
}

void Boss::P2Update()
{
	phaseTimer[1].Update();
	if (attackType == AttackType::Idle)
	{
		if (attackTimer[(int)AttackType::Idle].Check() >= 1000.0)
		{
			phaseTimer->Subtract(phaseTimer[1].Check() - 1000.0);
			ChangeAttack((AttackType)ApUtil::RNG(1, 2, true));
		}
	}
}

void Boss::P3Update()
{
	phaseTimer[2].Update();
	if (attackType == AttackType::Idle)
	{
		if (attackTimer[(int)AttackType::Idle].Check() >= 1000.0)
		{
			phaseTimer->Subtract(phaseTimer[2].Check() - 1000.0);
			ChangeAttack((AttackType)ApUtil::RNG(1, 2, true));
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

	//bullet状態の継続時間
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
}

void Boss::DrawAllAttacks()
{
	for (auto& attack : bossAttacks)
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
		break;
	case Boss::AttackType::Bar1:
		bossAttacks.emplace_back(new BossLaser((float)ApUtil::RNG(1, 360) * PI / 180));
		break;/*
	case Boss::AttackType::Bar2:
		break;*/
	case Boss::AttackType::AoE:
		bossAttacks.emplace_back(new BossAoE((float)ApUtil::RNG(1, 360) * PI / 180));
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
		return;
	}
	this->position = (Vec3)this->position + dir.SetLength(speed);
}

void Boss::DeadEffect()
{
	if (deadEffectTime < maxDeadEffectTime) {
		deadEffectTime++;
	}
	//プレイヤーが震える
	if (deadEffectTime <= 120) {
		//乱数シード生成器
		std::random_device seed_gen;
		//メルセンヌ・ツイスターの乱数エンジン
		std::mt19937_64 engine(seed_gen());
		//移動速度
		std::uniform_real_distribution<float> transDistX(-0.2f, 0.2f);
		std::uniform_real_distribution<float> transDistY(-0.2f, 0.2f);
		//プレイヤーが震える
		Vec3 dist = { transDistX(engine),transDistY(engine) ,0 };

		position = prePos + dist;
	}
	//爆発して周囲にエフェクトが散らばる
	else if (deadEffectTime <= 240) {
		//プレイヤーを消す
		isBossDisplay = false;
		if (deadEffectTime % 8 == 0) {
			std::unique_ptr<HitEffect> newEffect = std::make_unique<HitEffect>();
			newEffect->Ini(position, 4,true);
			deadEffect.emplace_back(std::move(newEffect));
		}
	}

	if (deadEffectTime >= 240) {
		if (deadEffect.size() <= 0) {
			isDead = true;
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
