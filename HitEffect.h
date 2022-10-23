#include <Object3D.h>
#include <PlayerOption.h>
#pragma once
class HitEffect
{
public:
	void Ini(Vec3 pos, float power);

	void Update();
	void Draw();
	bool GetAllDead() {return isAllDead;}
private:
	static const int maxNum = 15;
	Object3D obj_[maxNum];

	Vec3 speed_[maxNum];
	Vec3 rotSpeed[maxNum];
	Vec3 sclSpeed[maxNum];
	int aliveTime[maxNum];
	bool isAlive[maxNum];	//エフェクトが生きているか
	int deadCount;
	
	float colorBlue[maxNum];

	bool isAllDead = false;
};

