#include <ModelManager.h>
#include "Hpbar.h"

void Hpbar::Ini(float maxHp,Vec3 pos)
{
	//HPバーの初期化
	hpBar_.model = ModelManager::Get("Cube");
	hpBar_.position = pos;
	hpBar_.scale = { 5,1,1 };
	hpBar_.rotation = { 0,0,0 };
	hpBar_.UpdateMatrix();

	MaxHP_ = maxHp;
}

void Hpbar::Update(float nowHp)
{
	//現在HPでスケールを変化させる
	hpBar_.scale = { (float)(nowHp / 10),1,1 };
	//数値が０を下回らないようにする
	if (hpBar_.scale.x <= 0) {
		hpBar_.scale.x = 0;
	}
	hpBar_.UpdateMatrix();
}

void Hpbar::Draw()
{
	(*hpBar_.brightnessCB.contents) = Float4{ 0.7f, 0.3f, 0.3f, 1.0f };
	hpBar_.Draw("white");
}
