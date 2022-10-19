#include <ModelManager.h>
#include "Hpbar.h"

void Hpbar::Ini(float maxHp)
{
	//HPÉoÅ[ÇÃèâä˙âª
	hpBar_.model = ModelManager::Get("Cube");
	hpBar_.position = { 0,10,0 };
	hpBar_.scale = { 5,1,1 };
	hpBar_.rotation = { 0,0,0 };
	hpBar_.UpdateMatrix();

	MaxHP_ = maxHp;
}

void Hpbar::Update(float nowHp)
{
	hpBar_.scale = { (float)(nowHp / 10),1,1 };
	if (hpBar_.scale.x <= 0) {
		hpBar_.scale.x = 0;
	}
	hpBar_.UpdateMatrix();
}

void Hpbar::Draw()
{
	Float4 color{ 0.0f, 0.0f, 1.0f, 1.0f };
	(hpBar_.brightnessCB.contents) = &color;
	hpBar_.Draw("white");
}
