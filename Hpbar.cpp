#include <ModelManager.h>
#include "Hpbar.h"

void Hpbar::Ini(float maxHp,Vec3 pos)
{
	//HP�o�[�̏�����
	hpBar_.model = ModelManager::Get("Cube");
	hpBar_.position = pos;
	hpBar_.scale = { 5,1,1 };
	hpBar_.rotation = { 0,0,0 };
	hpBar_.UpdateMatrix();

	MaxHP_ = maxHp;
}

void Hpbar::Update(float nowHp)
{
	//����HP�ŃX�P�[����ω�������
	hpBar_.scale = { (float)(nowHp / 10),1,1 };
	//���l���O�������Ȃ��悤�ɂ���
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
