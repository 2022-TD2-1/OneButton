#pragma once
#include <Sprite.h>
class GameTimer
{
public:
	GameTimer();
	static GameTimer* GetInstance();

	void Ini();
	void Update();
	
	void StartTimer() { 
		time = clock();
		isStart = true;
	};
	void StopTimer() { isStart = false; };
	void DrawTimer();

	float GetTimer() { return timer; }
private:
	void DisplayTimerUpdate();
	int time;

	float timer;
	bool isStart;

	//表示する4つの数字を入れる変数
	float displayNum[5];
	//表示させる画像
	Sprite displayNumSprite[5];
	//数字画像
	Sprite numSprite[10];
	//小数点画像
	Sprite dotSprite;
};

