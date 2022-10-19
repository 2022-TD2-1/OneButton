#include <ModelManager.h>
#include "Hpbar.h"

void Hpbar::Ini(float maxHp)
{
	//HP�o�[�̏�����
	hpBar_.model = ModelManager::Get("Cube");
	hpBar_.position = { 0,10,0 };
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
	
	hpBar_.Draw("white");
}
