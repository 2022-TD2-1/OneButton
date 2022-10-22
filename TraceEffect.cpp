#include <random>
#include <ModelManager.h>
#include "TraceEffect.h"

void TraceEffect::Ini(Vec3 pos, Vec3 moveSpd)
{

	obj.model = ModelManager::Get("Sphere");
	obj.position = pos;
	moveSpd_ = moveSpd * 0.2f;

	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());
	//スケール
	std::uniform_real_distribution<float> sclDistX(0.3f, 0.4f);
	std::uniform_real_distribution<float> sclDistY(0.3f, 0.4f);
	std::uniform_real_distribution<float> sclDistZ(0.3f, 0.4f);
	float sclx = sclDistX(engine);
	float scly = sclDistX(engine);
	float sclz = sclDistX(engine);

	obj.scale = { sclx,scly,sclz };

	std::uniform_real_distribution<float> sclsubX(-0.05f, -0.03f);
	std::uniform_real_distribution<float> sclsubY(-0.05f, -0.03f);
	std::uniform_real_distribution<float> sclsubZ(-0.05f, -0.03f);
	sclx = sclsubX(engine);
	scly = sclsubY(engine);
	sclz = sclsubZ(engine);

	sclSpeed = { sclx,scly,sclz };

	obj.rotation = { 0,0,0 };

	obj.UpdateMatrix();
}

void TraceEffect::Update()
{
	if (obj.scale.x > 0) {
		obj.scale += sclSpeed;
	}
	if (obj.scale.x <= 0) {
		isDead = true;
	}

	obj.position += moveSpd_;

	obj.UpdateMatrix();
}

void TraceEffect::Draw()
{
	(*obj.brightnessCB.contents) = Float4{ 0.5f, 1.0f, 1.0f, 0.5f };
	obj.Draw("white");
}
