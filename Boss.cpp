#include "Boss.h"
#include <Parameters.h>
#include "ModelManager.h"
#include <ApUtil.h>
#include "BossBullet.h"
unique_ptr<Boss> Boss::current = nullptr;

void Boss::Init()
{
	Object3D::Object3D();
	this->model = ModelManager::Get("Sphere");

	for (auto& tm : phaseTimer) tm.Start();
	for (auto& tm : attackTimer) tm.Start();
	for (auto& tm : stateTimer) tm.Start();
	bulletTimer.Start();
}

void Boss::Update()
{
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
}

void Boss::Draw()
{
	Object3D::Draw("white");

	DrawAllAttacks();
}

void Boss::Hit(PlayerOption* other)
{
	this->health -= PlayerParams::damage;

	if (other->state == PlayerOption::State::Attack)
	{
		health -= 10;
		//kbˆ—
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
	}

	else if (other->state == PlayerOption::State::Move)
	{
		health -= 15;
		//kbˆ—
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
}

void Boss::P1Update()
{
	phaseTimer[0].Update();
	if (attackType == AttackType::Idle)
	{
		phaseTimer[0].Update();

		if (phaseTimer[0].Check() >= 1000.0)
		{
			phaseTimer->Subtract(phaseTimer[0].Check() - 1000.0);
			this->attackType = (AttackType)ApUtil::RNG(1, 3, true);
		}
	}
}

void Boss::P2Update()
{
}

void Boss::P3Update()
{
}

void Boss::IdleUpdate()
{
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
}

void Boss::Bar1Update()
{
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
