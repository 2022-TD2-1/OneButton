#include "Boss.h"
#include <Parameters.h>
#include "ModelManager.h"
#include <ApUtil.h>
#include "BossBullet.h"
#include "BossLaser.h"
#include <SceneManager.h>
#include <ResultScene.h>
unique_ptr<Boss> Boss::current = nullptr;

void Boss::Init()
{
	Object3D::Object3D();
	this->model = ModelManager::Get("Sphere");

	for (auto& tm : phaseTimer) tm.Start();
	for (auto& tm : attackTimer) tm.Start();
	for (auto& tm : stateTimer) tm.Start();
	bulletTimer.Start();

	hpBar_.Ini(maxHealth);
}

void Boss::Update()
{
	if (testTime >= 0) {
		testTime--;
		position = { 0,0,0 };
	}

	hpBar_.Update(health);

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

	this->col.x = this->position.x;
	this->col.y = this->position.y;
	this->col.r = this->scale.x;
	UpdateMatrix();

	UpdateAllAttacks();

	//エフェクト更新
	for (std::unique_ptr<HitEffect>& effect : hitEffect) {
		effect->Update();
	}
	//エフェクトをデリートする
	hitEffect.remove_if([](std::unique_ptr<HitEffect>& effect)
		{
			return effect->GetAllDead();
		});
}

void Boss::Draw()
{
	Object3D::Draw("white");

	DrawAllAttacks();

	hpBar_.Draw();
	//エフェクト描画
	for (std::unique_ptr<HitEffect>& effect : hitEffect) {
		effect->Draw();
	}
}

void Boss::Hit(PlayerOption* other)
{
	//this->health -= PlayerParams::damage;

	if (other->state == PlayerOption::State::Attack)
	{
		health -= 2.f;
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
		newEffect->Ini(position,*other);
		hitEffect.emplace_back(std::move(newEffect));
	}

	else if (other->state == PlayerOption::State::Move)
	{
		health -= 1.f;
		//kb処理
	}
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
			ChangeAttack((AttackType)ApUtil::RNG(1, 2, true));
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
}

void Boss::UpdateAllAttacks()
{
	for (auto itr = bossAttacks.begin(); itr != bossAttacks.end();)
	{
		(* itr)->Update();
		if (( * itr)->del)
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
		break;
	case Boss::AttackType::Bar2:
		break;
	case Boss::AttackType::AoE:
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

Boss* Boss::Create()
{
	current = unique_ptr<Boss>(new Boss);
	return current.get();
}

Boss* Boss::GetCurrent()
{
	return current.get();
}
