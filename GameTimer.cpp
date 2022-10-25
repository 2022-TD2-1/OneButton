#include <time.h>
#include "GameTimer.h"
#include <string>
#include <TextDrawer.h>

GameTimer::GameTimer()
{
	timer = 0;
	isStart = false;
}

GameTimer* GameTimer::GetInstance()
{
	static GameTimer instance;
	return &instance;
}

void GameTimer::Ini()
{
	time = 0;
	timer = 0;
	isStart = false;
}

void GameTimer::Update()
{
	if (isStart == true) {
		int i;
		clock_t oldTime, newTime;

		oldTime = clock();

		timer = ((float)(oldTime - time) / (float)CLOCKS_PER_SEC);


	}

}

void GameTimer::Draw()
{

}
