#pragma once
#include <Object3D.h>
class PlayerHP
{
public:
	void Ini(float posX);
	void Update();
	void Draw();

	void SetActive() { isActive = true; }
	bool GetActive() { return isActive; }
	bool GetDead() { return isDead; }
private:
	Object3D hpObj;
	bool isActive;
	bool isDead = false;
};

