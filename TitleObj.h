#pragma once
#include <CircleCollider.h>
#include "PlayerOption.h"
#include <Object3D.h>
class TitleObj : public Object3D
{
public:
	void Ini();
	void Update();
	void Draw();

	void Hit(PlayerOption* other);

	int GetHealth() { return health; }

	static TitleObj* Create();
	static TitleObj* GetCurrent();

	CircleCollider col;
private:
	static unique_ptr<TitleObj> current;
	

	int health = 100;

	
};

