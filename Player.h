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
#include <SoundManager.h>
#include <Camera.h>
#include <Sprite.h>

class Player :
	public Object3D
{
public:
	Player() {
		Object3D::Object3D();
		for (int i = 0; i < 2; i++)
		{
			auto& w = wall[i];
			w.model = ModelManager::Get("Cube");
			Matrix moveTemp = Matrix::Identity();
			moveTemp *= Matrix::Translation({ PlayerParams::circleR, 0.f, 0.f });
			moveTemp *= Matrix::RotZ(DegToRad(90 + 180 * i));

			//回転後の位置に移動して自身の行列を更新
			w.position = { moveTemp[3][0], moveTemp[3][1], moveTemp[3][2] };
			w.scale.x = 0.2f;
			w.UpdateMatrix();
		}
	};

	void Init(Camera* camera);

	void Update();
	void Draw();
	void DrawSprite();

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

	void SetCanAttack() { 
		isCanAttack = true; 

		bulletTimer.Start();
	}
	void SetCanNotAttack() { isCanAttack = false; }

	bool showWall = true;
private:
	static unique_ptr<Player> current;

private:
	void UpdateAllBullets();
	void DrawAllBullets();

	LimitedTimer bulletTimer = LimitedTimer((double)200.0f);
	float bulletSpeed = 0.32f;
	list<PlayerBullet> bullets;

	void RegisterBullet(Vec3 vel);

	std::list<unique_ptr<TraceEffect>> trsEffect_;

	//攻撃できるかフラグ
	bool isCanAttack = true;

	Camera* camera_ = nullptr;

	Sprite damageSprite;

	int bounceTimer = 0;
	int bounceTime = 20;

	Object3D wall[2];

	
};

