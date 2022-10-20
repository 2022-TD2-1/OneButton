#include <random>
#include <ModelManager.h>
#include "TraceEffect.h"

void TraceEffect::Ini(Vec3 pos)
{

	obj.model = ModelManager::Get("Cube");
	obj.position = pos;

	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());
	//スケール
	std::uniform_real_distribution<float> sclDistX(0.5f, 1.f);
	std::uniform_real_distribution<float> sclDistY(0.5f, 1.f);
	std::uniform_real_distribution<float> sclDistZ(0.5f, 1.f);
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

	obj.UpdateMatrix();
}

void TraceEffect::Draw()
{
	(*obj.brightnessCB.contents) = Float4{ 1.0f, 0.3f, 0.3f, 0.7f };
	obj.Draw("white");
}
