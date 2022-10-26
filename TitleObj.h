#pragma once
#include <CircleCollider.h>
#include "PlayerOption.h"
#include <Object3D.h>
#include "Hpbar.h"
#include <HitEffect.h>
#include <Camera.h>
class TitleObj : public Object3D
{
public:
	void Ini(Camera* camera);
	void Update();
	void Draw();

	void Hit(PlayerOption* other);

	int GetHealth() { return health; }
	bool GetDead() { return isDead; }

	static TitleObj* Create();
	static TitleObj* GetCurrent();

	CircleCollider col;
private:
	static unique_ptr<TitleObj> current;
	
	Hpbar hpBar_;

	int health = 100;

	bool isDead = false;

	Camera* camera_ = nullptr;
	//ヒット時エフェクト
	std::list< std::unique_ptr<HitEffect>> hitEffect;
};

