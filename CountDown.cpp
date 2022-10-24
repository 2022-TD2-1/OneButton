#include "ModelManager.h"
#include "CountDown.h"

void CountDown::Ini()
{
	numberObj[0].model = ModelManager::Get("Start");
	numberObj[0].position = { 0,0,-5 };
	numberObj[0].scale = { 3,3,3 };
	numberObj[0].UpdateMatrix();

	numberObj[1].model = ModelManager::Get("One");
	numberObj[1].position = { 0,0,-5 };
	numberObj[1].scale = { 3,3,3 };
	numberObj[1].UpdateMatrix();

	numberObj[2].model = ModelManager::Get("Two");
	numberObj[2].position = { 0,0,-5 };
	numberObj[2].scale = { 3,3,3 };
	numberObj[2].UpdateMatrix();

	numberObj[3].model = ModelManager::Get("Three");
	numberObj[3].position = { 0,0,-5 };
	numberObj[3].scale = { 3,3,3 };
	numberObj[3].UpdateMatrix();

}

void CountDown::Update()
{

	timer++;
	if (isActiveNum > 0) {
		if (timer >= 50) {
			timer = 0;
			isActiveNum--;
		}
	}

	if (isActiveNum == 0) {
		if (timer >= 50) {
			isEnd = true;
			isDisplay = false;
		}
	}
}

void CountDown::Draw()
{
	if (isDisplay == true) {
		numberObj[isActiveNum].Draw("white");
	}
}
