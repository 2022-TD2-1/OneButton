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

#pragma region 数字読み込み
	numSprite[0] = Sprite("Resources/Numbers/zero.png", "zero");
	numSprite[1] = Sprite("Resources/Numbers/one.png", "one");
	numSprite[2] = Sprite("Resources/Numbers/two.png", "two");
	numSprite[3] = Sprite("Resources/Numbers/three.png", "three");
	numSprite[4] = Sprite("Resources/Numbers/four.png", "four");
	numSprite[5] = Sprite("Resources/Numbers/five.png", "five");
	numSprite[6] = Sprite("Resources/Numbers/six.png", "six");
	numSprite[7] = Sprite("Resources/Numbers/seven.png", "seven");
	numSprite[8] = Sprite("Resources/Numbers/eight.png", "eight");
	numSprite[9] = Sprite("Resources/Numbers/nine.png", "nine");
	dotSprite = Sprite("Resources/Numbers/point.png", "point");
#pragma endregion
	for (int i = 0; i < 10; i++) {
		numSprite[i].position = { -100,-100,0 };
		numSprite[i].scale = { 0.5f,0.5f, 0.5f };
		numSprite[i].UpdateMatrix();
	}
	dotSprite.scale = { 0.5f,0.5f, 0.5f };
	dotSprite.UpdateMatrix();

}

void GameTimer::Update()
{
	if (isStart == true) {
		int i;
		clock_t oldTime, newTime;

		oldTime = clock();

		timer = ((float)(oldTime - time) / (float)CLOCKS_PER_SEC);
	}
	DisplayTimerUpdate();
}

void GameTimer::DrawTimer()
{
	const int display[5] =
	{ displayNum[0],displayNum[1], displayNum[2], displayNum[3], displayNum[4] };
	for (int i = 0; i < 5; i++) {
		//数字を描画
		displayNumSprite[i].Draw();
	}
	//小数点を描画
	dotSprite.Draw();
}

void GameTimer::DisplayTimerUpdate()
{
	//時間を代入する
	int time = (timer * 100);
	displayNum[0] = (time % 100000) / 10000;
	displayNum[1] = (time % 10000) / 1000;
	displayNum[2] = (time % 1000) / 100;
	displayNum[3] = (time % 100) / 10;
	displayNum[4] = (time % 10);

	int displayDist = 30;

	const int display[5] =
	{ displayNum[0],displayNum[1], displayNum[2], displayNum[3], displayNum[4] };
	for (int i = 0; i < 5; i++) {
		if (i == 3) {
			//小数点の座標を代入
			dotSprite.position.x = 100 + (displayDist * i);
			dotSprite.position.y = 350;
			dotSprite.position.z = 0;
		}

		//数字の座標を代入
		if (i <= 2) {
			numSprite[display[i]].position.x = 100 + (displayDist * i);
			numSprite[display[i]].position.y = 350;
			numSprite[display[i]].position.z = 0;
			displayNumSprite[i] = numSprite[display[i]];	//表示用スプライトに代入
		}
		else {
			numSprite[display[i]].position.x = 100 + (displayDist * (i + 1));
			numSprite[display[i]].position.y = 350;
			numSprite[display[i]].position.z = 0;
			displayNumSprite[i] = numSprite[display[i]];	//表示用スプライトに代入
		}
	}

	//スプライト更新
	for (int i = 0; i < 10; i++) {
		numSprite[i].UpdateMatrix();
		if (i < 4) {
			displayNumSprite[i].UpdateMatrix();
		}
	}
	dotSprite.UpdateMatrix();
}
