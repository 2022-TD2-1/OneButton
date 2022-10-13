#include "ResultScene.h"

void ResultScene::Init()
{
	//テスト用画像読み込み
	testSprite = Sprite("test");
	testSprite = Sprite("Resources/test.png","test");
	testSprite.position = { 128,128,0 };
}

void ResultScene::Update()
{
	testSprite.UpdateMatrix();
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
