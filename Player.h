#pragma once
#include "Object3D.h"
#include "Parameters.h"
#include <PlayerOption.h>
#include <ModelManager.h>
#include "TraceEffect.h"
#include "PlayerHP.h"
#include <PlayerBullet.h>
#include "HitEffect.h"
#include <Timer.h>

class Player :
	public Object3D
{
public:
	Player() {
		Object3D::Object3D();
	};

	void Init();

	void Update();
	void Draw();

	//HP系
	void Damage(int damage);
	static const int maxhealth = 3;
	int health = 3;
	const int maxCoolTime = 120;
	int coolTime = 0;
	list<PlayerHP> hps_;    //hpオブジェ
	Float4 color_;

	bool isDead = false;
	Vec3 prePos;	//プレイヤーのいた場所を保存する
	const int maxDeadEffectTime = 600;
	int deadEffectTime = 0;
	bool isPlayerDisplay = true;		//プレイヤーを表示するフラグ
	//ヒット時エフェクト
	std::list< std::unique_ptr<HitEffect>> deadEffect;
	void DeadEffect();	//死んだときの演出


	float x = 0.f;
	enum class Side {
		Clock,
		CounterClock
	} facing = Side::Clock;

	enum class State {
		Move,
		Stop
	} state = State::Move;

	//現在のプレイヤーのインスタンスを取得
	static Player* GetCurrent();

	//プレイヤーを初期化してCurrentに設定
	static Player* Create();

	CircleCollider col;

	void UpdateCollisionPos();

	list<PlayerOption> opti;

	void SetCanAttack() { isCanAttack = true; }
	void SetCanNotAttack() { isCanAttack = false; }
private:
	static unique_ptr<Player> current;

private:
	void UpdateAllBullets();
	void DrawAllBullets();

	LimitedTimer bulletTimer = LimitedTimer((double)500.0f);
	float bulletSpeed = 0.08f;
	list<PlayerBullet> bullets;

	void RegisterBullet(Vec3 vel);

	std::list<unique_ptr<TraceEffect>> trsEffect_;

	//攻撃できるかフラグ
	bool isCanAttack = true;
};

