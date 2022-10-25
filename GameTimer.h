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

	//•\¦‚·‚é4‚Â‚Ì”š‚ğ“ü‚ê‚é•Ï”
	float displayNum[5];
	//•\¦‚³‚¹‚é‰æ‘œ
	Sprite displayNumSprite[5];
	//”š‰æ‘œ
	Sprite numSprite[10];
	//¬”“_‰æ‘œ
	Sprite dotSprite;
};

