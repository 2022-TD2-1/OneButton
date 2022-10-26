#include "ModelManager.h"
#include "TitleObj.h"
#include <Player.h>


unique_ptr<TitleObj> TitleObj::current = nullptr;

void TitleObj::Ini(Camera* camera)
{
	model = ModelManager::Get("Knocker");
	position = { 0,0,0 };
	scale = { 2,2,2 };

	UpdateMatrix();

	hpBar_.Ini(health,Vec3(0,10,0));

	camera_ = camera;
}

void TitleObj::Update()
{

	col.x = position.x;
	col.y = position.y;
	col.r = scale.x;

	UpdateMatrix();

	hpBar_.Update(health);

	if (health <= 0) {
		isDead = true;
		Player::GetCurrent()->showWall = false;
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
}

void TitleObj::Draw()
{
	Object3D::Draw();

	hpBar_.Draw();

	//エフェクト描画
	for (std::unique_ptr<HitEffect>& effect : hitEffect) {
		effect->Draw();
	}
}

void TitleObj::Hit(PlayerOption* other)
{
	health -= 2 * (other->power * other->power);

	std::unique_ptr<HitEffect> newEffect = std::make_unique<HitEffect>();
	newEffect->Ini(position, other->power);
	hitEffect.emplace_back(std::move(newEffect));
	//カメラシェイク
	camera_->ShakeSet(20 * other->power, 0.3, other->power);
}



TitleObj* TitleObj::Create()
{
	current = unique_ptr<TitleObj>(new TitleObj);
	return current.get();
}

TitleObj* TitleObj::GetCurrent()
{
	return current.get();
}
