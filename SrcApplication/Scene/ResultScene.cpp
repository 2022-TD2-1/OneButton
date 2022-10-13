#include "ResultScene.h"

void ResultScene::Init()
{
	testSprite = Sprite("test");
	testSprite = Sprite("Resources/test.png","test");
}

void ResultScene::Update()
{
}

void ResultScene::DrawBack()
{
}

void ResultScene::Draw3D()
{
}

void ResultScene::DrawSprite()
{
	testSprite.Draw();
}
