#pragma once
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
	void Draw();

	float GetTimer() { return timer; }
private:
	int time;

	float timer;
	bool isStart;
};

