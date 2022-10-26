#pragma once
#include "Object3D.h"
#include <CircleCollider.h>
#include <ModelManager.h>
#include <SoundManager.h>
class PlayerOption :
	public Object3D
{
public:
	PlayerOption() { 
		Object3D::Object3D(); 
		model = ModelManager::Get("Player");
		scale = { .5f, .5f, .5f };
	};

	void Ini();
	void Update();
	void Draw();

	float x = 0;
	//TODO: Params‚Å‰Šú’l‚Æ‘‰Á—Ê‚ğİ’è‚·‚é
	float speed = 0;
	enum class Side {
		Clock,
		CounterClock
	} facing = Side::Clock;

	enum class State {
		Move,
		Attack,
		Back,
		Invis
	} state = State::Invis;

	void MoveUpdate();
	void AttackUpdate();
	void BackUpdate();
	void InvisUpdate();

	int stateTimer[4] = {};
	void ChangeState(State next);

	CircleCollider col = CircleCollider(99999, 99999, 0);

	float power = 1.0f;

	bool hasHit = false;

	Vec3 attackStartedPos;

	SoundKey playerAttack;
};

