#pragma once
#include <Object3D.h>
class CountDown
{
public:
	void Ini();
	void Update();
	void Draw();

	bool GetEnd() { return isEnd; }
	void SetDisplay() { isDisplay = true; }
private:
	Object3D numberObj[4];

	int isActiveNum = 3;

	int timer;

	bool isEnd = false;
	bool isDisplay = false;
};

