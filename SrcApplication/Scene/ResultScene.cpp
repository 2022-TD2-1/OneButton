#include "ResultScene.h"

void ResultScene::Init()
{
	//�e�X�g�p�摜�ǂݍ���
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
