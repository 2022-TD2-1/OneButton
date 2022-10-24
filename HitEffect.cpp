#include <random>
#include <ModelManager.h>
#include "HitEffect.h"

void HitEffect::Ini(Vec3 pos, float power, bool flag)
{
	for (int i = 0; i < maxNum; i++) {
		obj_[i].model = ModelManager::Get("Cube");
		obj_[i].position = pos;
		obj_[i].scale = { 0.3f * power,0.3f * power,0.3f * power };
		obj_[i].rotation = { 0,0,0 };

		//�����V�[�h������
		std::random_device seed_gen;
		//�����Z���k�E�c�C�X�^�[�̗����G���W��
		std::mt19937_64 engine(seed_gen());
		//�ړ����x
		std::uniform_real_distribution<float> transDistX(-0.1f * power, 0.1f * power);
		std::uniform_real_distribution<float> transDistY(-0.1f * power, 0.1f * power);
		//std::uniform_real_distribution<float> transDistZ(-50, 50);

		//�����G���W����n���A�w��͈͂��烉���_���Ȑ��l�𓾂�
		float x = transDistX(engine);
		float y = transDistY(engine);
		//float z = transDistZ(engine);

		speed_[i] = { x, y, 0 };

		//��]
		std::uniform_real_distribution<float> rotDistX(-0.05f * power, 0.05f * power);
		std::uniform_real_distribution<float> rotDistY(-0.05f * power, 0.05f * power);
		std::uniform_real_distribution<float> rotDistZ(-0.05f * power, 0.05f * power);
		float rotx = rotDistX(engine);
		float roty = rotDistY(engine);
		float rotz = rotDistZ(engine);

		rotSpeed[i] = { rotx,roty,rotz };

		//�X�P�[��
		std::uniform_real_distribution<float> sclDistX(-0.015f, -0.01f);
		std::uniform_real_distribution<float> sclDistY(-0.015f, -0.01f);
		std::uniform_real_distribution<float> sclDistZ(-0.015f, -0.01f);
		float sclx = sclDistX(engine);
		float scly = sclDistX(engine);
		float sclz = sclDistX(engine);

		sclSpeed[i] = { sclx,scly,sclz };

		//�G�t�F�N�g�������Ă��鎞��
		std::uniform_real_distribution<float> timeDist(40, 60);
		int time = timeDist(engine);
		aliveTime[i] = time;
		isAlive[i] = true;
		//�F�������_����
		std::uniform_real_distribution<float> colorDist(0.4f, 0.8f);
		if (flag == 0) {
			colorBlue[i] = colorDist(engine);
			ColorGreen[i] = 0.7f;
			ColorRed[i] = 0.3f;
		}
		else {
			colorBlue[i] = 0.2f;
			ColorGreen[i] = 0.2f;
			ColorRed[i] = colorDist(engine);
		}
	}
}

void HitEffect::Update()
{
	for (int i = 0; i < maxNum; i++) {
		if (isAlive[i] == true) {
			//�������œ��������_���̃X�s�[�h�𑫂��Ă���
			obj_[i].position += { speed_[i].x, speed_[i].y, 0 };
			obj_[i].rotation += { rotSpeed[i].x, rotSpeed[i].y, rotSpeed[i].z };
			obj_[i].scale += { sclSpeed[i].x, sclSpeed[i].y, sclSpeed[i].z };

			obj_[i].UpdateMatrix();

			if (aliveTime[i] > 0) aliveTime[i]--;
			//�^�C�}�[���[���ɂȂ�����\�����Ȃ�
			else if (aliveTime[i] <= 0) {
				deadCount++;
				isAlive[i] = false;
			};
			if (obj_[i].scale.x <= 0 || obj_[i].scale.y <= 0 || obj_[i].scale.z <= 0) {
				deadCount++;
				isAlive[i] = false;
			}
		}
	}
	if (deadCount == maxNum) {
		isAllDead = true;
	}

}

void HitEffect::Draw()
{
	for (int i = 0; i < maxNum; i++) {
		(*obj_[i].brightnessCB.contents) = Float4{ ColorRed[i], ColorGreen[i], colorBlue[i], 1.0f };

		if (isAlive[i] == true) {
			obj_[i].Draw("white");
		}
	}
}
