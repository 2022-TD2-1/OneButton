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

	//�\������4�̐���������ϐ�
	float displayNum[5];
	//�\��������摜
	Sprite displayNumSprite[5];
	//�����摜
	Sprite numSprite[10];
	//�����_�摜
	Sprite dotSprite;
};

