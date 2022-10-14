#include "Boss.h"
#include <Parameters.h>
#include "ModelManager.h"
unique_ptr<Boss> Boss::current = nullptr;

void Boss::Init()
{
	Object3D::Object3D();
	this->model = ModelManager::Get("Sphere");
}

void Boss::Update()
{
	void (Boss:: * BUpdtArray[]) () =
	{
		&Boss::CenterUpdate,
		&Boss::DownUpdate
	};

	(this->*BUpdtArray[(int)state])();

	this->col.x = this->position.x;
	this->col.y = this->position.y;
	this->col.r = this->scale.x;
}

void Boss::Draw()
{
	Object3D::Draw("white");
}

void Boss::Hit(PlayerOption* other)
{
	this->health -= PlayerParams::damage;

	if (other->state == PlayerOption::State::Attack)
	{
		health -= 10;
		//kbˆ—
	}

	else if (other->state == PlayerOption::State::Move)
	{
		health -= 15;
		//kbˆ—
	}
}

void Boss::CenterUpdate()
{
}

void Boss::DownUpdate()
{
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
